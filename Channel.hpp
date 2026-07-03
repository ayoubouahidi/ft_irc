#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <string>
#include <map>
#include <vector>


class Client;

class Channel {
    
    public:
        Channel(const std::string& name);
        const std::string& getName() const;
        const std::map<int, Client*>& getClients() const;
        void addClient(Client* client);
        void removeClient(Client* client);
    
        //getters 

        const std::string& getName();
        const std::string& getTopic();
        int getMemberCount() const;

        const std::map<int, Client*>& getMembers() const;
        const std::map<int, Client*>& getOperators() const;
    private:
        std::string             _name;
        std::string             _topic;
        std::map<int, Client*>  _members;    // fd → Client*
        std::map<int, Client*>  _operators;  // fd → Client*
        std::vector<int>        _inviteList; // fds of invited clients

        //mode
        bool        _inviteOnly;   // +i
        bool        _topicRestricted; // +t
        bool        _hasPassword;  // +k
        std::string _password;
        bool        _hasUserLimit; // +l
        int         _userLimit;

    
};



#endif


