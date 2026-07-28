#include "server.hpp"

void Server::addChannel(const std::string& name, Channel* channel)
{
	Channels[name] = channel;
}

void Server::removeChannel(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = Channels.find(name);
	if (it != Channels.end())
	{
		delete it->second;
		Channels.erase(it);
	}
}

Client* Server::getClientByNickname(const std::string& nickname)
{
	for (std::map<int, Client>::iterator it = Clients.begin(); it != Clients.end(); ++it)
	{
		if (it->second.getNickname() == nickname)
			return &it->second;
	}
	return NULL;
}

Channel* Server::getChannelByName(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = Channels.find(name);
	if (it == Channels.end())
		return NULL;
	return it->second;
}

std::string Server::getPassword() const
{
	return password;
}

void Server::broadcast(const std::string& message, const std::string& excludedNickname)
{
	for (std::map<int, Client>::iterator it = Clients.begin(); it != Clients.end(); ++it)
	{
		if (!excludedNickname.empty() && it->second.getNickname() == excludedNickname)
			continue;
		if (it->second.sendMsg(message))
    		enableEPOLLOUT(it->second.getFd());
	}
}

void Server::sendToClient(Client& client, const std::string& msg)
{
    if (client.sendMsg(msg))
        enableEPOLLOUT(client.getFd());
}

void Server::enableEPOLLOUT(int fd)
{
	epoll_event ev;

	ev.data.fd = fd;
	ev.events = EPOLLIN | EPOLLOUT;

	if (epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev) == -1)
	{
		std::cerr << "epol_ctl_mode error\n";
		return ;
	}
}

void Server::disableEPOLLOUT(int fd)
{
	epoll_event ev;

	ev.data.fd = fd;
	ev.events = EPOLLIN;

	if (epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev) == -1)
	{
		std::cerr << "epol_ctl_mode error\n";
		return ;
	}
}

Server::Server() : port(0), password("")
{}

Server::~Server()
{}

void Server::setPort(const size_t p) {port = p;}

void Server::setPaswd(const std::string& pswd) {password = pswd;}

size_t Server::getPort() const {return port;}

std::string Server::getPaswd() const {return password;}