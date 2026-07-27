#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"

// KICK #foot Youssef :Stop spamming stp
void kickCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.size() < 2)
    {
        client.sendMsg("461 :Not enough parameters");
        return;
    }

    std::string channelName = params[0];
    std::string targetName = params[1];
    std::string reason = "";

    if (params.size() > 2)
        reason = params[2];

    Channel *channel = server.getChannelByName(channelName);
    if (channel == NULL)
    {
        client.sendMsg("403 " + channelName + " :No such channel");
        return;
    }

    if (!channel->isMember(client.getFd()))
    {
        client.sendMsg("442 " + channelName + " :You're not on that channel");
        return;
    }

    if (!channel->isOperator(client.getFd()))
    {
        client.sendMsg("482 " + channelName + " :You're not channel operator");
        return;
    }

    Client *target = server.getClientByNickname(targetName);
    if (target == NULL || !channel->isMember(target->getFd()))
    {
        client.sendMsg("441 " + targetName + " " + channelName + " :They aren't on that channel");
        return;
    }

    std::string kickMsg = ":" + client.getNickname() + " KICK " + channelName + " " + targetName;
    if (!reason.empty())
    {
        kickMsg += " :" + reason;
    }
    channel->broadcast(kickMsg);

    int targetFd = target->getFd();
    channel->removeOperator(targetFd);
    channel->removeClient(target);
    if (channel->getMemberCount() == 0)
    {
        server.removeChannel(channelName);
    }
}