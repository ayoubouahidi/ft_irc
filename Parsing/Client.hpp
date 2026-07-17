#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <unistd.h>

typedef std::vector<std::string> writebuffer_t;



class Client {
    public:
        // ordical form 
        Client();
        Client(const Client& other);
        Client& operator=(const Client& other);
        Client(int fd);
        // getters and setters
        const std::string& getName() const;
        const std::string& getNickname() const;
        const std::string& getUsername() const;
        const std::string& getRealname() const;
        const std::string& getHostname() const;
        int getFd() const;
        const std::vector<std::string>& getChannels() const;
        bool getIsOperator() const;
        bool getIsRegistered() const;
        bool getIsPassVerified() const;
        const std::string& getReadBuffer() const;
        const std::string& getWriteBuffer() const;
        void setNickname(const std::string& nickname);
        void setUsername(const std::string& username);
        void setRealname(const std::string& realname);
        void setHostname(const std::string& hostname);
        void setFd(int fd);
        
        // other methods
        
        void addChannel(const std::string& channel);
        void removeChannel(const std::string& channel);
        void setIsOperator(bool isOperator);
        void setIsRegistered(bool isRegistered);
        void setIsPassVerified(bool isPassVerified);
        void setIsQuitting(bool isQuitting);
        void appendToReadBuffer(const std::string& data); // append to buff
        std::string getNextmessage(); // return the extracted message 
        void appendToWriteBuffer(const std::string& data); // 
        void        clearBuffer();
        void        sendMsg(const std::string& message) const;
        std::string getPrefix() const;
        

        ~Client();


    private:
        std::string nickname;
        std::string username;
        std::string realname;
        int fd;
        std::vector<std::string> channels;
        bool isOperator;
        bool isRegistered;
        bool isPassVerified;
        bool isQuitting;
        std::string readBuffer;
        std::string writeBuffer;
        std::string hostname;

};

#endif
