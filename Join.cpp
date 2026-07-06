#include "CommandHandler.hpp"

void joinCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        client.sendMsg("461 :Not enough parameters");
        return;
    }
    std::string channel = params[0];
    if (channel[0] != '#')
    {
        client.sendMsg("403 :No such channel");
        return;
    }

    Channel *channel_name_already_tacked = server.getChannelByName(channel);
    if (channel_name_already_tacked)
    {
        if (channel_name_already_tacked->isInviteOnly())
        {
            if (channel_name_already_tacked->isInvited(client.getFd()))
            {
                channel_name_already_tacked->removeInvite(client.getFd());
            }
            else
            {
                client.sendMsg("473 :Cannot join " + channel + "(+i)");
                return;
            }
        }

        if (channel_name_already_tacked->getUserLimit() > 0
            && channel_name_already_tacked->getMemberCount() >= channel_name_already_tacked->getUserLimit())
        {
            client.sendMsg("471 :Cannot join " + channel + " (+l)");
            return;
        }

        if (!channel_name_already_tacked->getPassword().empty())
        {
            if (params.size() < 2 || params[1] != channel_name_already_tacked->getPassword())
            {
                client.sendMsg("475 :Cannot join " + channel + " (+k)");
                return;
            }
        }

        channel_name_already_tacked->addClient(&client);
        client.addChannel(channel);

        std::string msgJoin = ":" + client.getNickname() + " JOIN :" + channel;
        channel_name_already_tacked->broadcast(msgJoin);

        client.sendMsg(":ft_irc 353 " + client.getNickname() + " = " + channel + " :<NAMES>");
        client.sendMsg(":ft_irc 366 " + client.getNickname() + " " + channel + " :End of /NAMES list.");
    }
    else
    {
        Channel *createNewChannel = new Channel(channel);
        if (!createNewChannel)
            return;

        createNewChannel->addOperator(&client);
        createNewChannel->addClient(&client);
        client.addChannel(channel);
        server.addChannel(channel, createNewChannel);

        std::string msgJoin = ":" + client.getNickname() + " JOIN :" + channel;
        createNewChannel->broadcast(msgJoin);

        client.sendMsg(":ft_irc 353 " + client.getNickname() + " = " + channel + " :<NAMES>");
        client.sendMsg(":ft_irc 366 " + client.getNickname() + " " + channel + " :End of /NAMES list.");
    }
}