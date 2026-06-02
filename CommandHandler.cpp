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


CommandHandler::CommandHandler(){
    _commands_map["PING"] = &myPingCommand;
}

void CommandHandler::executeCommand(Message& msg, Client& client, Server& server){
    if(_commands_map.find(msg.command) !=)
}