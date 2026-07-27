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
#include <sstream>

#define MAX_EVENTS 10
#include "../Parsing/Client.hpp"
#include "../Parsing/Channel.hpp"
#include "../Commands/CommandHandler.hpp"

struct Message;

// Function to parse IRC protocol messages
Message parseMessage(const std::string& line);

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
        CommandHandler _commandHandler;

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
        void        sendToClient(Client& client, const std::string& msg);
        void        enableEPOLLOUT(int fd);
        void        disableEPOLLOUT(int fd);

};

extern bool running;

#endif