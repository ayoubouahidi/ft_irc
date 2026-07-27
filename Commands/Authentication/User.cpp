#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"

void userCommand(Client &client, std::vector<std::string> &params, Server &server)
{
    (void)server;

    if (client.getIsRegistered())
    {
        server.sendToClient(client, "462 :You may not reregister");
        return;
    }

    if (params.size() < 4)
    {
        server.sendToClient(client, "461 USER :Not enough parameters");
        return;
    }

    client.setUsername(params[0]);
    client.setRealname(params[3]);

    registerClient(client, server);
}