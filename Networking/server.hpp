#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <fcntl.h>
#include <cerrno>
#include <sys/epoll.h>
#include <map>
#include <arpa/inet.h>
#include <signal.h>
#include "CommandHandler.hpp" // zdt 3ndk hadi

#define MAX_EVENTS 10

// struct Client
// {
//     int fd;
//     std::string written_data;
//     std::string read_data;
//     bool complete;
// };

class Server
{
    private :
        size_t port;
        std::string password;
        int serverSocket;
        int epollfd;
        struct epoll_event event;
        struct epoll_event events[MAX_EVENTS];
        std::map<int, Client> Clients;
        CommandHandler _commandHandler; // zdt 3ndk hadi
    public :
        Server();
        ~Server();
        void        setPort(const size_t p);
        void        setPaswd(const std::string& pswd);
        size_t      getPort() const; 
        std::string getPaswd() const;
        void        server_init();
        void        createSocket();
        void        setupEpoll();
        void        acceptClient();
        void        receiveFromClient(int fd);
};

extern bool running;

#endif