#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client{
    private:
        std::string nickname;
        std::string username;
        std::string realname;
        bool isRegistered;
        bool passVerified;
    public:
        std::string getNickName();
        std::string setNickName();
        std::string getUserName();
};

#endif