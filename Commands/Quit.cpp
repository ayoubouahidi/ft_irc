#include "CommandHandler.hpp"

void quitCommand(Client& client, std::vector<std::string>& params, Server& server) {
    std::string reason = "Client Quit";
    if (!params.empty()) {
        reason = params[0];
    }
    std::string fullMessage = ":" + client.getNickname() + " QUIT :" + reason;
    client.setIsQuitting(true);
    server.broadcast(fullMessage,client.getNickname());
}