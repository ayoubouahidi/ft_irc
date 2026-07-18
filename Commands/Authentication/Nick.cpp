#include "CommandHandler.hpp"
#include "../../Networking/server.hpp"





#include <string>
#include <cctype>

bool isValidNickname(const std::string &nick)
{
    if (nick.empty() || nick.size() > 9)
        return false;

    static const std::string special = "[]\\`_^{}|-";

    for (size_t i = 0; i < nick.size(); i++)
    {
        char c = nick[i];

        if (i == 0)
        {
            if (!std::isalpha(c) && !(special.find(c) != std::string::npos && c != '-'))
                return false;
        }
        else
        {
            if (!std::isalpha(c) && !std::isdigit(c) && special.find(c) == std::string::npos)
                return false;
        }
    }

    return true;
}


void nickCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        client.sendMsg("431 :No nickname given");
        return;
    }

    std::string nickname = params[0];
    if (!isValidNickname(nickname))
    {
        client.sendMsg("432 :Erroneous nickname");
        return;
    }

    Client *tmp = server.getClientByNickname(nickname);

    if (tmp)
    {
        if (tmp != &client)
        {
            client.sendMsg("433 :Nickname is already in use");
            return;
        }
    }

    bool wasRegistered =client.getIsRegistered();
    std::string oldNick = client.getNickname();

    client.setNickname(nickname);

    if (wasRegistered && oldNick != nickname)
        server.broadcast(":" + oldNick + " NICK :" + nickname, "");

    registerClient(client);
}