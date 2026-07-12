#include "CommandHandler.hpp"

void partCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    std::string reason = "";
    if (params.empty())
    {
        client.sendMsg("461 :Not enough parameters");
        return;
    }
    Channel *targetChannel = server.getChannelByName(params[0]);
    if (targetChannel)
    {
        if (!targetChannel->hasClient(&client))
        {
            client.sendMsg("442 " + params[0] + " :You're not on that channel");
            return;
        }
        else
        {
            std::string partMsg = ":" + client.getNickname() + " PART " + params[0];
            if (params.size() > 1)
            {
                partMsg += " :" + params[1];
            }

            targetChannel->broadcast(partMsg);
        }
        targetChannel->removeClient(&client);
        targetChannel->removeOperator(&client);
        size_t numbers_Member = targetChannel->getMemberCount();
        if(numbers_Member == 0){
            server.removeChannel(params[0]);
        }
    }
    else
    {
        client.sendMsg("403 " + params[0] + " :No such channel");
    }
}