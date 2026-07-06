#include "CommandHandler.hpp"

void registerClient(Client &client)
{
    if (client.getIsRegistered() || !client.getIsPassVerified() || client.getNickname().empty() || client.getUsername().empty())
        return;

    client.setIsRegistered(true);
    client.sendMsg(":ft_irc 001 " + client.getNickname() + " :Welcome to the ft_irc Network");
    client.sendMsg(":ft_irc 002 " + client.getNickname() + " :Your host is ft_irc, running version 1.0");
    client.sendMsg(":ft_irc 003 " + client.getNickname() + " :This server was created today");
    client.sendMsg(":ft_irc 004 " + client.getNickname() + " ft_irc 1.0 o o");
}