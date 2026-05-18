#include "Client.hpp"


// constructors

Client::Client(int fd) :  nickname(""), username(""), realname(""), hostname(""), fd(fd), isOperator(false), isRegistered(false) {
}
Client::Client() :  nickname(""), username(""), realname(""), hostname(""), fd(-1), isOperator(false), isRegistered(false) {
}
Client::Client(const Client& other) : nickname(other.nickname), username(other.username), realname(other.realname), hostname(other.hostname), fd(other.fd), channels(other.channels), isOperator(other.isOperator), isRegistered(other.isRegistered), readBuffer(other.readBuffer), writeBuffer(other.writeBuffer) {
}
Client& Client::operator=(const Client& other) {
    if (this != &other) {
        nickname = other.nickname;
        username = other.username;
        realname = other.realname;
        hostname = other.hostname;
        fd = other.fd;
        channels = other.channels;
        isOperator = other.isOperator;
        isRegistered = other.isRegistered;
        readBuffer = other.readBuffer;
        writeBuffer = other.writeBuffer;
    }
    return *this;
}


// getters

const std::string& Client::getName() const {
    return nickname;
}

const std::string& Client::getNickname() const {
    return nickname;
}
const std::string& Client::getUsername() const {
    return username;
}
const std::string& Client::getRealname() const {
    return realname;
}
const std::string& Client::getHostname() const {
    return hostname;
}
int Client::getFd() const {
    return fd;
}
const std::vector<std::string>& Client::getChannels() const {
    return channels;
}
bool Client::getIsOperator() const {
    return isOperator;
}
bool Client::getIsRegistered() const {
    return isRegistered;
}
const std::string& Client::getReadBuffer() const {
    return readBuffer;
}
const std::string& Client::getWriteBuffer() const {     
    return writeBuffer;
}   

// setters

void Client::setNickname(const std::string& nickname) {
    this->nickname = nickname;
}
void Client::setUsername(const std::string& username) {
    this->username = username;
}
void Client::setRealname(const std::string& realname) {
    this->realname = realname;
}
void Client::setHostname(const std::string& hostname) {
    this->hostname = hostname;
}
void Client::setFd(int fd) {
    this->fd = fd;
}       



Client::~Client() {
    close(fd);
}


void Client::appendToReadBuffer(const std::string& data)
{
    this->readBuffer = data + this->readBuffer;
}

std::string Client::getNextmessage()
{
    size_t pos = 0;
    std::string message;

    pos = this->readBuffer.find("\r\n");
    if (pos == std::string::npos)
        return "";
    message = readBuffer.substr(0 , pos);
    readBuffer.erase(0, pos);
    return message;
}

