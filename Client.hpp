#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client{
    private:
        std::string _nickname;
        std::string _username;
        std::string _realname;
        bool isRegistered;
        bool passVerified;
    public:
        std::string getNickName();
        std::string setNickName(std::string nick);
        std::string getUserName();
        std::string setUserName(std::string username);
};

#endif