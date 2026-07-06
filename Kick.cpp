#include "CommandHandler.hpp"

void kickCommand(Client& client, std::vector<std::string>& params, Server& server){
    std::string reason = "";
    if(params.size() < 2){
        client.sendMsg("461 :Not enough parameters");
        return;
    }

    std::string channelName = params[0];
    std::string targetName = params[1];

    Channel *channel = server.getChannelByName(channelName);
    if (channel == NULL) {
        client.sendMsg("403 " + channelName + " :No such channel");
        return;
    }

    if (!channel->isMember(client.getFd())) {
        client.sendMsg("442 " + channelName + " :You're not on that channel");
        return;
    }

    if(channel->isOperator(client.getFd())){
        Client *target = server.getClientByNickname(targetName);
        if(target){
            if(channel->isMember(target->getFd())){
                if(params.size() > 2){
                    reason = params[2];
                }else{
                    reason = "";
                }

                std::string kickMsg = ":" + client.getNickname() + " KICK " + channelName + " " + targetName;
                if (!reason.empty()) {
                    kickMsg += " :" + reason;
                }
                channel->broadcast(kickMsg);

                channel->removeClient(target);
                channel->removeOperator(target->getFd());
                if (channel->getMemberCount() == 0) {
                    server.removeChannel(channelName);
                }
            }else{
                client.sendMsg("441 " + targetName + " " + channelName + " :They aren't on that channel");
                return;
            }

        }else{
            client.sendMsg("441 " + targetName + " " + channelName + " :They aren't on that channel");
            return;
        }
    }else{
        client.sendMsg("482 " + channelName + " :You're not channel operator");
        return;
    }
}