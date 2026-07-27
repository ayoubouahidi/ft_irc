#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"

void privmsgCommand(Client& client, std::vector<std::string>& params, Server& server) {
    if (params.empty()) {
        server.sendToClient(client, "411 :No recipient given (PRIVMSG)");
        return;
    }
    if (params.size() < 2) {
        server.sendToClient(client, "412 :No text to send");
        return;
    }

    std::string target = params[0];
    std::string message = params[1];

    if (target[0] == '#') {
        Channel* channel = server.getChannelByName(target);
        if (!channel) {
            server.sendToClient(client, "401 " + target + " :No such nick/channel");
            return;
        }
        if (!channel->hasClient(&client)) {
            server.sendToClient(client, "404 " + target + " :Cannot send to channel");
            return;
        }
        std::string fullMsg = ":" + client.getNickname() + " PRIVMSG " + target + " :" + message;
        channel->broadcast(fullMsg, &client);
        return;
    }

    Client* resclient = server.getClientByNickname(target);
    if (!resclient) {
        server.sendToClient(client, "401 " + target + " :No such nick/channel");
        return;
    }

    std::string fullMsg = ":" + client.getNickname() + " PRIVMSG " + target + " :" + message;
    resclient->sendMsg(fullMsg);
}