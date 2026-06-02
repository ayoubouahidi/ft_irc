#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client{
    private:
        std::string _nickname;
        std::string _username;
        std::string _realname;
        bool _isRegistered;
        bool _passVerified;
    public:
        std::string getNickName();
        std::string setNickName(std::string nickname);
        std::string getUserName();
        std::string setUserName(std::string username);
        
};

#endif