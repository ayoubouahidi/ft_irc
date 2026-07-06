#include "CommandHandler.hpp"

void userCommand(Client& client, std::vector<std::string>& params,  Server& server){
    (void)server;
    if(client.getIsRegistered()){
        client.sendMsg("462 : Unauthorized command (already registred)");
        return;
    }

    if(params.size() < 4){
        client.sendMsg("461 :Not enough parameters");
        return;
    }
    if (client.getIsPassVerified() == true && client.getNickname().empty() == false) {
        
        client.setIsRegistered(true);
        client.sendMsg(":ft_irc 001 " + client.getNickname() + " :Welcome to the ft_irc Network");
        client.sendMsg(":ft_irc 002 " + client.getNickname() + " :Your host is ft_irc, running version 1.0");
        client.sendMsg(":ft_irc 003 " + client.getNickname() + " :This server was created today");
        client.sendMsg(":ft_irc 004 " + client.getNickname() + " ft_irc 1.0 o o");
    }

    client.setUsername(params[0]);
    client.setRealname(params[3]);
}