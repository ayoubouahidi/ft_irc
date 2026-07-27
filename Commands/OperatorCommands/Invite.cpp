#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"

void inviteCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.size() < 2)
    {
        server.sendToClient(client, "461 :Not enough parameters");
        return;
    }

    std::string targetName = params[0];
    std::string channelName = params[1];

    Client *targetUser = server.getClientByNickname(targetName);
    if (!targetUser)
    {
        server.sendToClient(client, "401 " + targetName + " :No such nick/channel");
        return;
    }

    Channel *channel = server.getChannelByName(channelName);
    if (!channel)
    {
        server.sendToClient(client, "403 " + channelName + " :No such channel");
        return;
    }

    if (!channel->isMember(client.getFd()))
    {
        server.sendToClient(client, "442 " + channelName + " :You're not on that channel");
        return;
    }

    if (channel->isMember(targetUser->getFd()))
    {
        server.sendToClient(client, "443 " + targetName + " " + channelName + " :is already on channel");
        return;
    }

    if (channel->isInviteOnly() && !channel->isOperator(client.getFd()))
    {
        server.sendToClient(client, "482 " + channelName + " :You're not channel operator");
        return;
    }

    channel->addInvite(targetUser->getFd());
    targetUser->sendMsg(":" + client.getNickname() + " INVITE " + targetName + " :" + channelName);
    server.sendToClient(client, ":ft_irc 341 " + client.getNickname() + " " + targetName + " " + channelName);
}