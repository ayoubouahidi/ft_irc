#include "CommandHandler.hpp"
#include "Client.hpp"
#include "Server.hpp"

int main(){
    std::string _message;
    std::string text = "PING :123";
    CommandHandler cmdH;
    Client mytestclient;
Server mytestserver;
    Message Msg = cmdH.parseMessage(text);
    cmdH.executeCommand(Msg, );
}
