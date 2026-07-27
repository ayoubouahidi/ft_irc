#include "../CommandHandler.hpp"
#include "../../Networking/server.hpp"

void passCommand(Client& client, std::vector<std::string>& params, Server& server){
    if(params.empty() && !client.getIsRegistered()){
        server.sendToClient(client, "461 :Not enough parameters");
        return;
    }
    if(client.getIsRegistered()){
        server.sendToClient(client, "462 :Unauthorized command (already registered)");
        return;
    }
    if(params[0] == server.getPaswd()){
        client.setIsPassVerified(true);
        registerClient(client, server);
    }else{
        server.sendToClient(client, "464 :Password incorrect");
    }
}