#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

class Server{
    private:
        std::string _password;
        int _serverfd;
        int _port;
    public:
        Server(std::string password);
        std::string getPassword() const;
        void initServer();
        void ft_run();
};

#endif