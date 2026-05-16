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

struct Client
{
    int fd;
    std::string written_data;
    std::string read_data;
    bool complete;
};

std::map<int, Client> Clients;

#endif