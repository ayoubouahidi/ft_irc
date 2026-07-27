#include "Client.hpp"
#include <sys/socket.h>


// constructors

Client::Client(int fd) :  nickname(""), username(""), realname(""), fd(fd), channels(), isOperator(false), isRegistered(false), isPassVerified(false), isQuitting(false), readBuffer(""), writeBuffer(""), hostname("") {
}
Client::Client() :  nickname(""), username(""), realname(""), fd(-1), channels(), isOperator(false), isRegistered(false), isPassVerified(false), isQuitting(false), readBuffer(""), writeBuffer(""), hostname("") {
}
Client::Client(const Client& other) : nickname(other.nickname), username(other.username), realname(other.realname), fd(other.fd), channels(other.channels), isOperator(other.isOperator), isRegistered(other.isRegistered), isPassVerified(other.isPassVerified), isQuitting(other.isQuitting), readBuffer(other.readBuffer), writeBuffer(other.writeBuffer), hostname(other.hostname) {
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
        isPassVerified = other.isPassVerified;
        isQuitting = other.isQuitting;
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
bool Client::getIsPassVerified() const {
    return isPassVerified;
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

void Client::addChannel(const std::string& channel) {
    if (std::find(channels.begin(), channels.end(), channel) == channels.end())
        channels.push_back(channel);
}

void Client::removeChannel(const std::string& channel) {
    channels.erase(std::remove(channels.begin(), channels.end(), channel), channels.end());
}

void Client::setIsOperator(bool isOperator) {
    this->isOperator = isOperator;
}

void Client::setIsRegistered(bool isRegistered) {
    this->isRegistered = isRegistered;
}

void Client::setIsPassVerified(bool isPassVerified) {
    this->isPassVerified = isPassVerified;
}

void Client::setIsQuitting(bool isQuitting) {
    this->isQuitting = isQuitting;
}



Client::~Client() {}


void Client::appendToReadBuffer(const std::string& data)
{
    this->readBuffer = data + this->readBuffer;
}

std::string Client::getNextmessage()
{
    size_t pos = 0;
    std::string message;

    pos = this->readBuffer.find("\n");
    if (pos == std::string::npos)
        return "";
    message = readBuffer.substr(0 , pos);
    readBuffer.erase(0, pos + 2);
    return message;
}


void Client::clearBuffer()
{
    this->readBuffer.clear();
    this->writeBuffer.clear();
}

bool Client::flushWriteBuffer()
{
    while (!writeBuffer.empty())
    {
        ssize_t n = send(fd, writeBuffer.c_str(), writeBuffer.size(), 0);

        if (n > 0)
            writeBuffer.erase(0, n);
        else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
            return false;
        else
            throw std::runtime_error("send error");
    }
    return true;
}

bool Client::sendMsg(const std::string& message)
{
    std::string msg = message + "\r\n";

    if (!writeBuffer.empty())
    {
        writeBuffer += msg;
        return true;
    }

    ssize_t n = send(fd, msg.c_str(), msg.size(), 0);

    if (n == (ssize_t)msg.size())
        return false;
    else if (n == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            writeBuffer += msg;
            return true;
        }
        else
            throw std::runtime_error("send error");
        return false;
    }
    else // 0 <= n < msg.size()
    {
        writeBuffer.append(msg.begin() + n, msg.end());
        return true;
    }
}

std::string Client::getPrefix() const
{
    std::string prefix = ":" + this->nickname + "!" + this->username + "@" + this->hostname;
    return prefix;
}
