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


int Channel::getMemberCount() const {
    return _members.size();
}

const std::string& Channel::getPassword() const {
    return _password;
}

const std::map<int, Client*>& Channel::getMembers() const {
    return _members;
}

const std::map<int, Client*>& Channel::getOperators() const {
    return _operators;
}

const std::string& Channel::getTopic() {
    return _topic;
}

int Channel::getUserLimit() const {
    return _userLimit;
}

bool Channel::isInviteOnly() const {
    return _inviteOnly;
}
bool Channel::isTopicRestricted() const {
    return _topicRestricted;
}
bool Channel::hasPassword() const {
    return _hasPassword;
}

bool Channel::hasUserLimit() const {
    return _hasUserLimit;
}

void Channel::addMember(Client* client) {
    _members[client->getFd()] = client;
}

void Channel::removeMember(int fd) {
    _members.erase(fd);
    _operators.erase(fd);
}

bool Channel::isMember(int fd) const {
    return _members.find(fd) != _members.end();
}

void Channel::addOperator(Client* client) {
    _operators[client->getFd()] = client;
}

void Channel::removeOperator(int fd) {
    _operators.erase(fd);
}

bool Channel::isOperator(int fd) const {
    return _operators.find(fd) != _operators.end();
}

void Channel::addInvite(int fd) {
    _inviteList.push_back(fd);
}

bool Channel::isInvited(int fd) const {
    return std::find(_inviteList.begin(), _inviteList.end(), fd) != _inviteList.end();
}

void Channel::removeInvite(int fd) {
    _inviteList.erase(std::remove(_inviteList.begin(), _inviteList.end(), fd), _inviteList.end());
}

void Channel::setTopic(const std::string& topic) {
    _topic = topic;
}

void Channel::setInviteOnly(bool val) {
    _inviteOnly = val;
}

void Channel::setTopicRestricted(bool val) {
    _topicRestricted = val;
}

void Channel::setPassword(const std::string& password) {
    _password = password;
    _hasPassword = true;
}

void Channel::removePassword() {
    _password.clear();
    _hasPassword = false;
}

void Channel::setUserLimit(int limit) {
    _userLimit = limit;
    _hasUserLimit = true;
}

void Channel::removeUserLimit() {
    _userLimit = 0;
    _hasUserLimit = false;
}



void Channel::addClient(Client* client) {
    _members[client->getFd()] = client;
}

void Channel::removeClient(Client* client) {
    _members.erase(client->getFd());
    _operators.erase(client->getFd());
}

void Channel::broadcast(const std::string& message, int excludeFd) {
    for (std::map<int, Client*>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        if (it->first != excludeFd) {
            it->second->sendMsg(message);
        }
    }
}
