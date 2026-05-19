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

struct Client
{
    int fd;
    std::string written_data;
    std::string read_data;
    bool complete;
};

class Server
{
    private :
        size_t port;
        std::string password;
    public :
        Server();
        ~Server();
        void        setPort(const size_t p);
        void        setPaswd(const std::string& pswd);
        size_t      getPort() const; 
        std::string getPaswd() const;
        int         server_init();
};

extern bool running;
extern std::map<int, Client> Clients;

#endif