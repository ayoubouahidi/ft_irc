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
        std::string getUserName();
        void setNickName(std::string nickname);
        void setUserName(std::string username);
        std::string getRealName();
        void setRealName(std::string realname);
};

#endif