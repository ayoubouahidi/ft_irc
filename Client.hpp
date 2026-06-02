#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>


class Client{
    private:
        std::string _nickname;
        std::string _username;
        std::string _realname;
        bool _isRegistered;
        bool _passVerified;
    public:

        //setters
        void setNickName(std::string nickname);
        void setUserName(std::string username);
        void setRealName(std::string realname);
        void setIsRegistered(bool status);
        void setIsPassVerified(bool status);
        
        //getters
        std::string getNickName();
        std::string getUserName();
        std::string getRealName();
        bool getIsRegistered();
        bool getIsPassVerified();


        void sendMessage(std::string msg);

};

#endif