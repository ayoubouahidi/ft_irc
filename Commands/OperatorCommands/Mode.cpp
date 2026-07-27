#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"


void modeCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        server.sendToClient(client, "461 :Not enough parameters");
        return;
    }

    std::string nameChannel = params[0];

    if (nameChannel.empty() || nameChannel[0] != '#')
    {
        server.sendToClient(client, "502 :Cant change mode for other users");
        return;
    }

    Channel *channel = server.getChannelByName(nameChannel);
    if (!channel)
    {
        server.sendToClient(client, "403 " + nameChannel + " :No such channel");
        return;
    }

    if (params.size() == 1)
    {
        std::string activeModes = "+";
        if (channel->isInviteOnly())
            activeModes += "i";
        if (channel->isTopicRestricted())
            activeModes += "t";
        if (!channel->getPassword().empty())
            activeModes += "k";
        if (channel->getUserLimit() > 0)
            activeModes += "l";

        server.sendToClient(client, "324 " + client.getNickname() + " " + nameChannel + " " + activeModes);
        return;
    }

    if (!channel->isOperator(&client))
    {
        server.sendToClient(client, "482 " + nameChannel + " :You're not channel operator");
        return;
    }

    bool isAdding = true;
    std::string mode = params[1];
    size_t argIndex = 2;

    for (size_t i = 0; i < mode.size(); i++)
    {
        char c = mode[i];

        if (c == '+')
        {
            isAdding = true;
        }
        else if (c == '-')
        {
            isAdding = false;
        }
        else if (c == 'i')
        {
            channel->setInviteOnly(isAdding);
        }
        else if (c == 't')
        {
            channel->setTopicRestricted(isAdding);
        }
        else if (c == 'k')
        {
            if (isAdding)
            {
                if (argIndex < params.size())
                {
                    channel->setPassword(params[argIndex]);
                    argIndex++;
                }
            }
            else
            {
                channel->setPassword("");
            }
        }
        else if (c == 'l')
        {
            if (isAdding)
            {
                if (argIndex < params.size())
                {
                    int limit = 0;
                    std::stringstream ss(params[argIndex]);
                    ss >> limit;
                    if (limit > 0)
                        channel->setUserLimit(limit);
                    argIndex++;
                }
            }
            else
            {
                channel->setUserLimit(0);
            }
        }
        else if (c == 'o')
        {
            if (argIndex < params.size())
            {
                Client *target = server.getClientByNickname(params[argIndex]);
                if (target && channel->isMember(target))
                {
                    if (isAdding)
                        channel->addOperator(target);
                    else
                        channel->removeOperator(target);
                }
                argIndex++;
            }
        }
        else
        {
            std::string unknownchar(1, c);
            server.sendToClient(client, "472 " + unknownchar + " :is unknown mode char to me");
        }
    }

    std::string message = ":" + client.getNickname() + " MODE " + nameChannel + " " + mode;
    for (size_t i = 2; i < argIndex && i < params.size(); i++)
    {
        message += " " + params[i];
    }
    channel->broadcast(message);
}
