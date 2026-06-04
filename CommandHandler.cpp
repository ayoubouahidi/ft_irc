#include "CommandHandler.hpp"


Message CommandHandler::parseMessage(const std::string& raw){
    Message msg;
    std::istringstream iss(raw);

    std::string prefix;
    iss >> prefix;
    if(prefix[0] == ':'){
        msg.prefix = prefix;
        iss >> msg.command;
    }else
        msg.command = prefix;
    std::string params;
    while (iss >> params)
    {
        if(params[0] == ':')
            params = params.substr(1);
        msg.paramters.push_back(params);
    }
    std::cout << "it's prefix : " << msg.prefix << std::endl;
    std::cout << "it's command : " << msg.command << std::endl;
    for(size_t i = 0; i < msg.paramters.size(); i++){
        std::cout << "it's parameters : " << msg.paramters[i] << std::endl;
    }
    return msg;
}


void myPingCommand(Client& client, std::vector<std::string>& params, Server& server) {
    std::cout << "==== PING COMMAND IS RUNNING! ====" << std::endl;
}

void passCommand(Client& client, std::vector<std::string>& params, Server& server){
    //chech password is empty
    if(params.empty()){
        client.sendMessage("461 :Not enough parameters");
        return;
    }
    if(client.getIsRegistered()){
        client.sendMessage("462 :Unauthorized command (already registered)");
        return;
    }

    if(params[0] == server.getPassword()){
        client.setIsPassVerified(true);
    }else{
        client.sendMessage("464 :Password incorrect");
    }
}


CommandHandler::CommandHandler(){
    _commands_map["PING"] = &myPingCommand;
    _commands_map["PASS"] = &passCommand;
    _commands_map["NICK"] = &nickCommand;
}



void nickCommand(Client& client,std::vector<std::string>& params, Server& server){
    if(params.empty()){
        client.sendMessage("431: No nickname given");
        return;
    }
    client.setNickName(params[0]);
}

void CommandHandler::executeCommand(Message& msg, Client& client, Server& server){
    if(_commands_map.find(msg.command) != _commands_map.end()){
        _commands_map[msg.command](client, msg.paramters,server);
    }else{
        std::cout << "Command [" << msg.command << "] not found." << std::endl;
    }
}