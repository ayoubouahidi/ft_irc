#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"

class Client;

class Server
{
    void processClientBuffer(Client &client);
}

#endif