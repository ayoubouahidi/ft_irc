#include "CommandHandler.hpp"

void myPingCommand(Client& client, std::vector<std::string>& params, Server& server) {
    (void)server;
    if(params.empty()){
        client.sendMsg("409: No origin specified !");
        return;
    }
    std::string pongMessage = "PONG :" + params[0];
    client.sendMsg(pongMessage);
}