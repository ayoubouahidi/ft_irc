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
        std::string restOfline;
        if(params[0] == ':'){
            params = params.substr(1);
            std::getline(iss,restOfline);
            msg.paramters.push_back(params + restOfline);
            break;
        }else{
            msg.paramters.push_back(params);
        }
    }
    std::cout << "it's prefix : " << msg.prefix << std::endl;
    std::cout << "it's command : " << msg.command << std::endl;
    for(size_t i = 0; i < msg.paramters.size(); i++){
        std::cout << "it's parameters : " << msg.paramters[i] << std::endl;
    }
    return msg;
}


void myPingCommand(Client& client, std::vector<std::string>& params, Server& server) {
    if(params.empty()){
        client.sendMessage("409: No origin specified !");
        return;
    }
    std::string pongMessage = "PONG:" + params[0];
    client.sendMessage(pongMessage);
}

void passCommand(Client& client, std::vector<std::string>& params, Server& server){
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

void nickCommand(Client& client,std::vector<std::string>& params, Server& server){
    if(params.empty()){
        client.sendMessage("431: No nickname given");
        return;
    }
    std::string wantedname = params[0];
    for(size_t i = 0; i < wantedname.size() ;i++){
        if(wantedname[i] == ' ' || wantedname[i] == '#'){
            client.sendMessage("432 :Erroneous nickname");
            return;
        }
    }
    client.setNickName(params[0]);
}

void userCommand(Client& client, std::vector<std::string>& params,  Server& server){
    if(client.getIsRegistered()){
        client.sendMessage("462 : Unauthorized command (already registred)");
        return;
    }

    if(params.size() < 4){
        client.sendMessage("461 :Not enough parameters");
        return;
    }
    if (client.getIsPassVerified() == true && client.getNickName().empty() == false) {
        
        client.setIsRegistered(true);
        client.sendMessage(":ft_irc 001 " + client.getNickName() + " :Welcome to the ft_irc Network");
        client.sendMessage(":ft_irc 002 " + client.getNickName() + " :Your host is ft_irc, running version 1.0");
        client.sendMessage(":ft_irc 003 " + client.getNickName() + " :This server was created today");
        client.sendMessage(":ft_irc 004 " + client.getNickName() + " ft_irc 1.0 o o");
    }

    client.setUserName(params[0]);
    client.setRealName(params[3]);

}


void quitCommand(Client& client, std::vector<std::string>& params, Server& server) {
    std::string reason = "Client Quit";
    if (!params.empty()) {
        reason = params[0];
    }
    std::cout << "Client " << client.getNickName() << " is quitting. Reason: " << reason << std::endl;
    client.setIsQuitting(true);
}



CommandHandler::CommandHandler(){
    _commands_map["PING"] = &myPingCommand;
    _commands_map["PASS"] = &passCommand;
    _commands_map["NICK"] = &nickCommand;
    _commands_map["USER"] = &userCommand;
    _commands_map["QUIT"] = &quitCommand;
}





void CommandHandler::executeCommand(Message& msg, Client& client, Server& server){
    if(_commands_map.find(msg.command) != _commands_map.end()){
        _commands_map[msg.command](client, msg.paramters,server);
    }else{
        std::cout << "Command [" << msg.command << "] not found." << std::endl;
    }
}