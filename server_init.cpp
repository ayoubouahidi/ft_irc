#include "server.hpp"

std::map<int, Client> Clients;

int Server::server_init()
{
    int serverSocket;

    //creating a socket here!
    //AF_INET FOR IPV4
    //SOCK_STREAM FOR TCP CONNECTION and 0 is a default for it
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        throw std::runtime_error("socket issue");
    //specifying the server address cuz it has important data for binding
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
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
    fcntl(serverSocket, F_SETFL, O_NONBLOCK);

    //managing sockets with epoll
    int epollfd;
    struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];
    epollfd = epoll_create1(0);
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event);

    //connecting sockets
    //one while! 
    while (running)
    {
        int num_events = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < num_events; i++)
        {
            if (events[i].data.fd == serverSocket)
            {
                // while (1)
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
                        fcntl(newsocket, F_SETFL, O_NONBLOCK);  
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
            }
            else
            {
                char buffer[1024] = {0};
                int n = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                int fd = events[i].data.fd;
                Client& client = Clients[fd]; // just for readability! instead of Clients[new_client.fd].fd
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
                    close(fd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
                    //erase this fd's client's data from the map!
                    Clients.erase(fd);
                    std::cout << "block end" << std::endl;
                }
                else
                {
                    throw std::runtime_error("chihaja!");
                }
                //here check the response! sendv
            }
        }  
    }
    close(serverSocket);
    close(epollfd);
    return 0;
}