#include "CommandHandler.hpp"

void passCommand(Client& client, std::vector<std::string>& params, Server& server){
    if(params.empty()){
        client.sendMsg("461 :Not enough parameters");
        return;
    }
    if(client.getIsRegistered()){
        client.sendMsg("462 :Unauthorized command (already registered)");
        return;
    }

    if(params[0] == server.getPaswd()){
        client.setIsPassVerified(true);
        registerClient(client);
    }else{
        client.sendMsg("464 :Password incorrect");
    }
}