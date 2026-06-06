#include "CommandHandler.hpp"
#include "Client.hpp"
#include "Server.hpp"

int main(){
    std::string _message;
    std::string text = "USER hamza 0 * :Hamza User";
    CommandHandler cmdH;
    Client mytestclient;
    Server mytestserver("1234");
    Message Msg = cmdH.parseMessage(text);
    cmdH.executeCommand(Msg, mytestclient, mytestserver);

    std::cout << "--- SENDING PASS ---" << std::endl;
    Message passMsg = cmdH.parseMessage("PASS 1234");
    cmdH.executeCommand(passMsg, mytestclient, mytestserver);

    std::cout << "\n--- SENDING NICK ---" << std::endl;
    Message nickMsg = cmdH.parseMessage("NICK mySuperNick");
    cmdH.executeCommand(nickMsg, mytestclient, mytestserver);

    std::cout << "\n--- SENDING QUIT ---" << std::endl;
    Message quitMsg = cmdH.parseMessage(":hamza!user@host QUIT :Leaving");
    cmdH.executeCommand(quitMsg,mytestclient,mytestserver);

}
