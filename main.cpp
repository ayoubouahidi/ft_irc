#include "CommandHandler.hpp"
#include "Client.hpp"
#include "Server.hpp"

int main(){
    std::string _message;
    std::string text = "USER hamza 0 * :Hamza User";
    CommandHandler cmdH;
    Client mytestclient;
    Server mytestserver;
    Message Msg = cmdH.parseMessage(text);
    cmdH.executeCommand(Msg, mytestclient, mytestserver);
}
