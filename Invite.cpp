#include "CommandHandler.hpp"

void inviteCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.size() < 2)
    {
        client.sendMessage("461 :Not enough parameters");
        return;
    }

    std::string targetName = params[0];
    std::string channelName = params[1];

    Client *targetUser = server.getClientByNickname(targetName);
    if (!targetUser)
    {
        client.sendMessage("401 " + targetName + " :No such nick/channel");
        return;
    }

    Channel *channel = server.getChannelByName(channelName);
    if (!channel)
    {
        client.sendMessage("403 " + channelName + " :No such channel");
        return;
    }

    if (!channel->hasClient(&client)) {
        client.sendMessage("442 " + channelName + " :You're not on that channel");
        return;
    }

    if (channel->hasClient(targetUser)) {
        client.sendMessage("443 " + targetName + " " + channelName + " :is already on channel");
        return;
    }

    if (channel->getIsInviteOnly() && !channel->isOperator(&client)) {
        client.sendMessage("482 " + channelName + " :You're not channel operator");
        return;
    }

    channel->inviteUser(targetName);
    targetUser->sendMessage(":" + client.getNickName() + " INVITE " + targetName + " :" + channelName);
    client.sendMessage(":ft_irc 341 " + client.getNickName() + " " + targetName + " " + channelName);
}