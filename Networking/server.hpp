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

#define MAX_EVENTS 10
#include "../Parsing/Client.hpp"
#include "../Parsing/Channel.hpp"

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
        std::map<std::string, Channel*> Channels;
    public :
        Server();
        ~Server();
        void        setPort(const size_t p);
        void        setPaswd(const std::string& pswd);
        size_t      getPort() const; 
        std::string getPaswd() const;
        void        addChannel(const std::string& name, Channel* channel);
        void        removeChannel(const std::string& name);
        Client*     getClientByNickname(const std::string& nickname);
        Channel*    getChannelByName(const std::string& name);
        std::string getPassword() const;
        void        broadcast(const std::string& message, const std::string& excludedNickname);
        void        server_init();
        void        createSocket();
        void        setupEpoll();
        void        acceptClient();
        void        receiveFromClient(int fd);
};

extern bool running;

#endif