#include "server.hpp"

void    Server::createSocket()
{
    //creating a socket here!
    //AF_INET FOR IPV4
    //SOCK_STREAM FOR TCP CONNECTION and 0 is a default for it
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        throw std::runtime_error("socket issue");
    //specifying the server address cuz it has important data for binding
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    //it helps rebinding the same port if an issue occured (like ctrl+c)
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //binding ip/port to the server
    if (bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        throw std::runtime_error("bind error");

    //listenning to clients requests 5 max
    if (listen(serverSocket, 5) == -1)
        throw std::runtime_error("listen error");
}

void    Server::setupEpoll()
{
    epollfd = epoll_create1(0);
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event);
}

void    Server::acceptClient()
{
    int newsocket = accept(serverSocket, nullptr, nullptr);
    if (newsocket != -1)
    {
        Client new_client;
        new_client.fd = newsocket;
        new_client.read_data = "";
        new_client.written_data = "";
        new_client.complete = false;
        Clients[new_client.fd] = new_client;
        event.events = EPOLLIN | EPOLLET; //epollet makes the kernel notify only when there's new data
        event.data.fd = newsocket;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, newsocket, &event);
    }
    else
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            std::cout << "block end" << std::endl;
        else
            std::cout << "real recv error";
    }
}

void    Server::receiveFromClient(int fd)
{
    char buffer[1024] = {0};
    int n = recv(fd, buffer, sizeof(buffer), 0);
    int new_fd = fd;
    Client& client = Clients[new_fd]; // just for readability! instead of Clients[new_client.fd].fd
    if (n > 0)
    {
        client.read_data.append(buffer, n);
        //request parser here!
        // if (client.complete == true) if we found /r/r/n then flag it with true
        std::cout << "client : " << client.read_data;
    }
    else if (errno == EAGAIN || errno == EWOULDBLOCK)//delete later
        std::cout << "block end" << std::endl;
    else if (n == 0)
    {
        close(new_fd);
        epoll_ctl(epollfd, EPOLL_CTL_DEL, new_fd, &event);
        //erase this fd's client's data from the map!
        Clients.erase(new_fd);
        std::cout << "block end" << std::endl;
    }
    else
        return ;    
    //here check the response! sendv
}

void    Server::server_init()
{
    //creating a socket here!
    createSocket();
    //managing sockets with epoll
    setupEpoll();
    //connecting sockets
    //one while! 
    while (running)
    {
        int num_events = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < num_events; i++)
        {
            if (events[i].data.fd == serverSocket)
                acceptClient();
            else
                receiveFromClient(events[i].data.fd);
        }  
    }
    close(serverSocket);
    close(epollfd);
}