#include "CommandHandler.hpp"
#include "../../Networking/server.hpp"

void registerClient(Client &client)
{
    if (client.getIsRegistered())
        return;

    if (!client.getIsPassVerified())
        return;

    if (client.getNickname().empty())
        return;

    if (client.getUsername().empty())
        return;

    client.setIsRegistered(true);

    client.sendMsg(":ft_irc 001 " + client.getNickname() + " :Welcome\n");
    client.sendMsg(":ft_irc 002 " + client.getNickname() + " :Your host is ft_irc\n");
    client.sendMsg(":ft_irc 003 " + client.getNickname() + " :Server created today\n");
    client.sendMsg(":ft_irc 004 " + client.getNickname() + " ft_irc 1.0 o o\n");
}