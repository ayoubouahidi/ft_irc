#include "CommandHandler.hpp"


void inviteCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.size() < 2)
    {
        client.sendMsg("461 :Not enough parameters");
        return;
    }

    std::string targetName = params[0];
    std::string channelName = params[1];

    Client *targetUser = server.getClientByNickname(targetName);
    if (!targetUser)
    {
        client.sendMsg("401 " + targetName + " :No such nick/channel");
        return;
    }

    Channel *channel = server.getChannelByName(channelName);
    if (!channel)
    {
        client.sendMsg("403 " + channelName + " :No such channel");
        return;
    }

    if (!channel->isMember(client.getFd()))
    {
        client.sendMsg("442 " + channelName + " :You're not on that channel");
        return;
    }

    if (channel->isMember(targetUser->getFd()))
    {
        client.sendMsg("443 " + targetName + " " + channelName + " :is already on channel");
        return;
    }

    if (channel->isInviteOnly() && !channel->isOperator(client.getFd()))
    {
        client.sendMsg("482 " + channelName + " :You're not channel operator");
        return;
    }

    channel->addInvite(targetUser->getFd());
    targetUser->sendMsg(":" + client.getNickname() + " INVITE " + targetName + " :" + channelName);
    client.sendMsg(":ft_irc 341 " + client.getNickname() + " " + targetName + " " + channelName);
}