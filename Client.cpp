#include "Client.hpp"


Client::Client(){
    _isRegistered = false;
    _passVerified = false;
    _isQuitting = false;
}

void Client::setNickName(std::string nickname){
    _nickname = nickname;
}

void Client::setUserName(std::string username){
    _username = username;
}

void Client::setRealName(std::string realname){
    _realname = realname;
}

void Client::setIsRegistered(bool status){
    _isRegistered = status;
}

void Client::setIsPassVerified(bool status){
    _passVerified = status;
}

void Client::setIsQuitting(bool status){
    _isQuitting = status;
}


std::string Client::getNickName(){
    return _nickname;
}

std::string Client::getUserName(){
    return _username;
}

std::string Client::getRealName(){
    return _realname;
}
bool Client::getIsRegistered(){
    return _isRegistered;
}

bool Client::getIsPassVerified(){
    return _passVerified;
}

bool Client::getIsQuitting(){
    return _isQuitting;
}



void Client::sendMessage(std::string msg){
    std::cout <<"-> Sending to client: " << msg << std::endl;
}