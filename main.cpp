#include "CommandHandler.hpp"
#include "Client.hpp"
#include "Server.hpp"

int main(){
    std::string _message;
    std::string text = ":server 001 hamza :Welcome to ft_irc";
    CommandHandler cmdH;
    Client mytestclient;
    Server mytestserver;
    Message Msg = cmdH.parseMessage(text);
    cmdH.executeCommand(Msg, mytestclient, mytestserver);
}
