#include "CommandHandler.hpp"
#include "../Networking/server.hpp"

CommandHandler::CommandHandler()
{
    _commands_map["PASS"] = &passCommand;
    _commands_map["NICK"] = &nickCommand;
    _commands_map["USER"] = &userCommand;
    _commands_map["JOIN"] = &joinCommand;
    _commands_map["PRIVMSG"] = &privmsgCommand;
    _commands_map["KICK"] = &kickCommand;
    _commands_map["INVITE"] = &inviteCommand;
    _commands_map["TOPIC"] = &topicCommand;
    _commands_map["MODE"] = &modeCommand;
}

void CommandHandler::executeCommand(Message &msg, Client &client, Server &server)
{
    if (_commands_map.find(msg.command) != _commands_map.end())
    {
        _commands_map[msg.command](client, msg.paramters, server);
    }
    else
    {
        std::cout << "Command [" << msg.command << "] not found." << std::endl;
    }
}