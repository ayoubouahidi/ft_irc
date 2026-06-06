#include "Server.hpp"

Server::Server(std::string password) {
    _password = password;
}

std::string Server::getPassword() const {
    return _password;
}

void Server::initServer(){

}

void Server::ft_run(){
}
