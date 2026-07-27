#include "Channel.hpp"
#include "Client.hpp"
#include <algorithm>


Channel::Channel(const std::string& name) : _name(name), _topic(""), _inviteOnly(false), _topicRestricted(false), _hasPassword(false), _password(""), _hasUserLimit(false), _userLimit(0) {
}

const std::string& Channel::getName() const {
    return _name;
}

std::vector<Client*> Channel::getClients() const {
    std::vector<Client*> clients;
    for (std::map<int, Client*>::const_iterator it = _members.begin(); it != _members.end(); ++it)
        clients.push_back(it->second);
    return clients;
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

void Channel::removeMember(Client* client) {
    if (client)
        removeMember(client->getFd());
}

bool Channel::isMember(int fd) const {
    return _members.find(fd) != _members.end();
}

bool Channel::isMember(Client* client) const {
    return client && isMember(client->getFd());
}

bool Channel::hasClient(Client* client) const {
    return client && isMember(client->getFd());
}

bool Channel::hasClient(int fd) const {
    return isMember(fd);
}

void Channel::addOperator(Client* client) {
    _operators[client->getFd()] = client;
}

void Channel::removeOperator(int fd) {
    _operators.erase(fd);
}

void Channel::removeOperator(Client* client) {
    if (client)
        removeOperator(client->getFd());
}

bool Channel::isOperator(int fd) const {
    return _operators.find(fd) != _operators.end();
}

bool Channel::isOperator(Client* client) const {
    return client && isOperator(client->getFd());
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

void Channel::broadcast(const std::string& message, Client* excludeClient) {
    if (excludeClient)
        broadcast(message, excludeClient->getFd());
    else
        broadcast(message, -1);
}
