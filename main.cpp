#include "CommandHandler.hpp"

int main(){
    std::string _message;
    std::string text = "PING :123 hamza yass ibw";
    CommandHandler cmdH;
    cmdH.parseMessage(text);
}