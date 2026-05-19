#include "server.hpp"

Server::Server() : port(0), password("")
{}

Server::~Server()
{}

void Server::setPort(const size_t p) {port = p;}

void Server::setPaswd(const std::string& pswd) {password = pswd;}

size_t Server::getPort() const {return port;}

std::string Server::getPaswd() const {return password;}