#include "CommandHandler.hpp"

void modeCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        client.sendMsg("461 :Not enough parameters");
        return;
    }
    std::string nameChannel = params[0];
    if (nameChannel[0] == '#')
    {
    }
    else
    {
        client.sendMsg("502 :Cant change mode for other users");
        return;
    }
    Channel *channel = server.getChannelByName(nameChannel);
    if (channel)
    {
        if (params.size() == 1)
        {
            std::string activeModes = "+";
            if (channel->isInviteOnly())
            {
                activeModes += "i";
            }
            if (channel->isTopicRestricted())
            {
                activeModes += "t";
            }
            if (!channel->getPassword().empty())
            {
                activeModes += "k";
            }
            if (channel->getUserLimit() > 0)
            {
                activeModes += "l";
            }
            client.sendMsg("324 " + client.getNickname() + " " + params[0] + " " + activeModes);
            return;
        }
        else
        {
            if (channel->isOperator(&client))
            {
                bool isAdding = true;
                std::string mode = params[1];
                size_t argIndex = 2;
                for (size_t i = 0; i < mode.size(); i++)
                {
                    if (mode[i] == '+')
                    {
                        isAdding = true;
                    }
                    else if (mode[i] == '-')
                    {
                        isAdding = false;
                    }
                    else if (mode[i] == 'i')
                    {
                        channel->setInviteOnly(isAdding);
                    }
                    else if (mode[i] == 't')
                    {
                        channel->setTopicRestricted(isAdding);
                    }
                    else if (mode[i] == 'k')
                    {
                        if (isAdding) {
                            if (argIndex < params.size()) {
                                channel->setPassword(params[argIndex]);
                                argIndex++;
                            }
                        } else {
                            channel->setPassword("");
                        }
                    }else if(mode[i] == 'l'){
                        int limit = 0;
                        if (isAdding) {
                            if (argIndex < params.size()) {
                                std::stringstream ss(params[argIndex]);
                                ss >> limit;
                                channel->setUserLimit(limit);
                                argIndex++;
                            }
                        } else {
                            channel->setUserLimit(0);
                        }
                    }
                    else if (mode[i] == 'o')
                    {
                        if (argIndex < params.size()) {
                            Client* target = server.getClientByNickname(params[argIndex]);
                            if (target) {
                                if (isAdding) {
                                    channel->addOperator(target);
                                } else {
                                    channel->removeOperator(target);
                                }
                            }
                            argIndex++;
                        }
                    }
                    else
                    {
                        std::string unknownchar(1, mode[i]);
                        client.sendMsg("472 " + unknownchar + " :is unknown mode char to me");
                    }
                }
                std::string message = ":" + client.getNickname() + " MODE " + params[0] + " " + params[1];
                // Zid l-parametres f l-message dyal l-broadcast (bhal s-miya awla password)
                for (size_t i = 2; i < argIndex; i++) {
                    if (i < params.size()) {
                        message += " " + params[i];
                    }
                }
                channel->broadcast(message);
            }
            else
            {
                client.sendMsg("482 " + params[0] + " :You're not channel operator");
                return;
            }
        }
    }
    else
    {
        client.sendMsg("403 " + params[0] + " :No such channel");
        return;
    }
}