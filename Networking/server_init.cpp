#include "server.hpp"
#include <map>

Message parseMessage(const std::string &line)
{
    Message msg;
    std::istringstream iss(line);
    std::string token;

    // Check for prefix (starts with :)
    if (!line.empty() && line[0] == ':')
    {
        iss >> token;
        msg.prefix = token.substr(1); // Remove the leading ':'
    }

    if (iss >> token)
    {
        msg.command = token;
        // Convert command to uppercase
        for (size_t i = 0; i < msg.command.size(); i++)
            msg.command[i] = std::toupper(msg.command[i]);
    }

    size_t trailingPos = line.find(" :");
    if (trailingPos != std::string::npos)
    {
        std::string beforeTrailing = line.substr(0, trailingPos);
        std::istringstream paramIss(beforeTrailing);
        if (!line.empty() && line[0] == ':')
            paramIss >> token; // Skip prefix
        paramIss >> token;     // Skip command
        while (paramIss >> token)
            msg.paramters.push_back(token);
        std::string trailing = line.substr(trailingPos + 2); // +2 to skip " :"
        if (!trailing.empty())
            msg.paramters.push_back(trailing);
    }
    else
    {
        while (iss >> token)
            msg.paramters.push_back(token);
    }
    return msg;
}

void Server::createSocket()
{
    // creating a socket here!
    // AF_INET FOR IPV4
    // SOCK_STREAM FOR TCP CONNECTION and 0 is a default for it
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "socket issue\n";
        return ;
    }
    // specifying the server address cuz it has important data for binding
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // it helps rebinding the same port if an issue occured (like ctrl+c)
    int opt = 1;
    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        std::cerr << "setsockopt error\n";
        return ;
    }

    // binding ip/port to the server
    if (bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "bind error\n";
        return ;
    }

    // listenning to clients requests 5 max
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "listen error\n";
        return ;
    }

    if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
    {
        std::cerr << "fcntl error\n";
        return ;
    }
}

void Server::setupEpoll()
{
    epollfd = epoll_create1(0);
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event);
}

void Server::acceptClient()
{
    int newsocket = accept(serverSocket, 0, 0);
    if (newsocket != -1)
    {
        if (fcntl(newsocket, F_SETFL, O_NONBLOCK) == -1)
        {
            std::cerr << "fcntl failed\n";
            close(newsocket);
            return ;
        }
        Clients[newsocket] = Client(newsocket);
        event.events = EPOLLIN;
        event.data.fd = newsocket;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, newsocket, &event) == -1)
        {
            std::cerr << "epoll_ctl error\n";
            Clients.erase(newsocket);
            close(newsocket);
            return ;
        }
    }
    else
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return ; // no more clients
        std::cerr << "accept error\n";
        return ;
    }
}

void Server::receiveFromClient(int fd)
{
    char buffer[1024] = {0};
    static std::map<int, std::string> pending_data;
    Client &client = Clients[fd];
    int n = recv(fd, buffer, sizeof(buffer), 0);

    if (n > 0)
    {
        pending_data[fd].append(buffer, n);
        while (true)
        {
            size_t pos = pending_data[fd].find("\n");
            if (pos == std::string::npos)
                break;
            std::string line = pending_data[fd].substr(0, pos);
            if (!line.empty() && line[line.size() - 1] == '\r')
                line.erase(line.size() - 1);
            pending_data[fd].erase(0, pos + 1);
            // //COMMAND PARSING HNA 3YT FUNC(CLIENT, LINE);
            Message msg = parseMessage(line);
            _commandHandler.executeCommand(msg, client, *this);
        }
    }
    else if (n == 0)
    {
        epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
        pending_data.erase(fd);
        close(fd);
        Clients.erase(fd);
    }
    else
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
        pending_data.erase(fd);
        close(fd);
        Clients.erase(fd);
        std::cerr << "receive error\n";
        return ;
    }
}

void Server::server_init()
{
    // creating a socket here!
    createSocket();
    // managing sockets with epoll
    setupEpoll();
    // connecting sockets
    while (running)
    {
        int num_events = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < num_events; i++)
        {
            if (events[i].data.fd == serverSocket)
                acceptClient();
            else
            {
                if (events[i].events & EPOLLIN)
                    receiveFromClient(events[i].data.fd);
                if (events[i].events & EPOLLOUT)
                {

                    Client& client = Clients[events[i].data.fd];
                    if (client.flushWriteBuffer())
                        disableEPOLLOUT(client.getFd());
                }
            }
        }
    }
    close(serverSocket);
    close(epollfd);
}