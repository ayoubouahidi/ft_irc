#include "CommandHandler.hpp"
#include "../../Networking/server.hpp"


static std::string buildNamesList(Channel *chan)
{
    std::vector<Client *> members = chan->getClients();
    std::string names;

    for (size_t i = 0; i < members.size(); i++)
    {
        if (chan->isOperator(members[i]))
            names += "@";
        names += members[i]->getNickname();
        if (i + 1 < members.size())
            names += " ";
    }
    return names;
}

static void sendNamesReply(Client &client, const std::string &channel, Channel *chan)
{
    std::string names = buildNamesList(chan);
    client.sendMsg(":ft_irc 353 " + client.getNickname() + " = " + channel + " :" + names);
    client.sendMsg(":ft_irc 366 " + client.getNickname() + " " + channel + " :End of /NAMES list.");
}

static void joinSingleChannel(Client &client, const std::string &channel, const std::string &key, Server &server)
{
    if (channel.empty() || channel[0] != '#')
    {
        client.sendMsg(":ft_irc 403 " + client.getNickname() + " " + channel + " :No such channel");
        return;
    }

    Channel *chan = server.getChannelByName(channel);

    if (chan)
    {
        if (chan->isMember(client.getFd()))
            return;

        if (chan->isInviteOnly())
        {
            if (chan->isInvited(client.getFd())){}
            else
            {
                client.sendMsg(":ft_irc 473 " + client.getNickname() + " " + channel + " :Cannot join channel (+i)");
                return;
            }
        }
        if (!chan->getPassword().empty() && key != chan->getPassword())
        {
            client.sendMsg(":ft_irc 475 " + client.getNickname() + " " + channel + " :Cannot join channel (+k)");
            return;
        }
        if (chan->getUserLimit() > 0 && chan->getMemberCount() >= chan->getUserLimit())
        {
            client.sendMsg(":ft_irc 471 " + client.getNickname() + " " + channel + " :Cannot join channel (+l)");
            return;
        }

        chan->addClient(&client);
        client.addChannel(channel);

        std::string msgJoin = ":" + client.getNickname() + " JOIN :" + channel;
        chan->broadcast(msgJoin);

        sendNamesReply(client, channel, chan);
    }
    else
    {
        Channel *newChannel = new Channel(channel);

        newChannel->addOperator(&client);
        newChannel->addClient(&client);
        client.addChannel(channel);
        server.addChannel(channel, newChannel);

        std::string msgJoin = ":" + client.getNickname() + " JOIN :" + channel;
        newChannel->broadcast(msgJoin);

        sendNamesReply(client, channel, newChannel);
    }
}

void joinCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        client.sendMsg(":ft_irc 461 " + client.getNickname() + " JOIN :Not enough parameters");
        return;
    }

    std::vector<std::string> channels;
    std::vector<std::string> keys;

    std::stringstream chanStream(params[0]);
    std::string tmp;
    while (std::getline(chanStream, tmp, ','))
        channels.push_back(tmp);

    if (params.size() >= 2)
    {
        std::stringstream keyStream(params[1]);
        while (std::getline(keyStream, tmp, ','))
            keys.push_back(tmp);
    }

    for (size_t i = 0; i < channels.size(); i++)
    {
        if (i < keys.size())
            joinSingleChannel(client, channels[i], keys[i], server);
        else
            joinSingleChannel(client, channels[i], "", server);
    }
}