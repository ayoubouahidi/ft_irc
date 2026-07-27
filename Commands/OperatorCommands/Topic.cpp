#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"

void topicCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        client.sendMsg("461 :Not enough parameters");
        return;
    }

    Channel *channel = server.getChannelByName(params[0]);
    if (!channel)
    {
        client.sendMsg("403 " + params[0] + " :No such channel");
        return;
    }

    if (!channel->isMember(client.getFd()))
    {
        client.sendMsg("442 " + params[0] + " :You're not on that channel");
        return;
    }

    if (params.size() < 2)
    {
        if (channel->getTopic().empty()) {
            client.sendMsg("331 " + params[0] + " :No topic is set");
        } else {
            client.sendMsg("332 " + params[0] + " :" + channel->getTopic());
        }
    }
    else
    {
        if (channel->isTopicRestricted() && !channel->isOperator(client.getFd())) {
            client.sendMsg("482 " + params[0] + " :You're not channel operator");
            return;
        }
        
        std::string newTopic = params[1];
        channel->setTopic(newTopic);
        
        std::string topicMsg = ":" + client.getNickname() + " TOPIC " + params[0] + " :" + newTopic;
        channel->broadcast(topicMsg);
    }
}