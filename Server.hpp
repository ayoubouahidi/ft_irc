#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server{
    private:
        std::string _password;
    public:
        Server(std::string password);
        std::string getPassword() const;
};

#endif