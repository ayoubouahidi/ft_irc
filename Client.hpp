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
        //getters
        void setNickName(std::string nickname);
        void setUserName(std::string username);
        void setRealName(std::string realname);
        void isRegistered()
        
        //setters
        std::string getNickName();
        std::string getUserName();
        std::string getRealName();
};

#endif