#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <unistd.h>
#include "Client.hpp"
#include "Server.hpp"


class Client;
class Server;

struct Message
{
    std::string prefix;
    std::string command;
    std::vector<std::string> paramters;
};

typedef void (*CommandFunction)(Client&, std::vector<std::string>&, Server&);

class CommandHandler{
    private:
        std::map<std::string, CommandFunction> _commands_map;
    public:
        CommandHandler();
        Message parseMessage(const std::string& raw);
        void executeCommand(Message& msg, Client& client, Server& server);
};






#endif