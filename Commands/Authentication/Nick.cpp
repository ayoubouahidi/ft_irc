#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp" 

void nickCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    if (params.empty())
    {
        server.sendToClient(client, "431 :No nickname given");
        return;
    }

    std::string nickname = params[0];

    for (size_t i = 0; i < nickname.size(); i++)
    {
        if (nickname[i] == '#' || nickname[i] == '*' || nickname[i] == ':')
        {
            server.sendToClient(client, "432 :Erroneous nickname");
            return;
        }
    }

    Client *tmp = server.getClientByNickname(nickname);

    if (tmp && tmp != &client)
    {
        server.sendToClient(client, "433 :Nickname is already in use");
        return;
    }

    std::string oldNick = client.getNickname();

    client.setNickname(nickname);

    if (client.getIsRegistered() && !oldNick.empty() && oldNick != nickname)
        server.broadcast(":" + oldNick + " NICK :" + nickname, "");

    registerClient(client, server);
}