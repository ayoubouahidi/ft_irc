#include "Channel.hpp"
#include "Client.hpp"


Channel::Channel(const std::string& name) : _name(name), _topic(""), _inviteOnly(false), _topicRestricted(false), _hasPassword(false), _password(""), _hasUserLimit(false), _userLimit(0) {
}

Channel::~Channel() {
    
}

Channel::Channel(const Channel& other) : _name(other._name), _topic(other._topic), _members(other._members), _operators(other._operators), _inviteList(other._inviteList), _inviteOnly(other._inviteOnly), _topicRestricted(other._topicRestricted), _hasPassword(other._hasPassword), _password(other._password), _hasUserLimit(other._hasUserLimit), _userLimit(other._userLimit) {
}

Channel& Channel::operator=(const Channel& other) {
    if (this != &other) {
        _name = other._name;
        _topic = other._topic;
        _members = other._members;
        _operators = other._operators;
        _inviteList = other._inviteList;
        _inviteOnly = other._inviteOnly;
        _topicRestricted = other._topicRestricted;
        _hasPassword = other._hasPassword;
        _password = other._password;
        _hasUserLimit = other._hasUserLimit;
        _userLimit = other._userLimit;
    }
    return *this;
}

const std::string& Channel::getName() const {
    return _name;
}

const std::map<int, Client*>& Channel::getClients() const {
    return _members;
}

void Channel::addClient(Client* client) {
    _members[client->getFd()] = client;
}

void Channel::removeClient(Client* client) {
    _members.erase(client->getFd());
    _operators.erase(client->getFd());
}

