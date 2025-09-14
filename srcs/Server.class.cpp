/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:04:45 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:46 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

Server::Server(std::string const & port, std::string const & password, struct tm *timeinfo)
:  _servSocketFd(-1), _password(password), _infos(NULL)
{
	_port = atoi(port.c_str());
	this->setTime(timeinfo);
}

Server::~Server() 
{
	for (channel_iterator it = _ChannelTable.begin(); it != _ChannelTable.end(); ++it) {
		delete it->second;
	}
	_ChannelTable.clear();
	for (client_iterator it = _ClientTable.begin(); it != _ClientTable.end(); it++)
	{
		close (it->second->getFd());
		delete it->second;
	}
	_ClientTable.clear();
	close(_servSocketFd);
}
bool	Server::_signal = false;

void	Server::handeSignal(int signum)
{
	(void)signum;
	_signal = true;
}

void	Server::setTime(struct tm * timeinfo)
{
	char buffer[100];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	std::string time(buffer);

	_time = time;
}

int	Server::getPort() const
{
	return this->_port;
}

int	Server::getSocketFd() const
{
	return this->_servSocketFd;
}

std::string const & Server::getPassword() const
{
	return this->_password;
}

Client *	Server::getClient(std::string const & nickname)
{
	client_iterator it = _ClientTable.begin();

	while (it != _ClientTable.end())
	{
		if (nickname.compare(it->second->getNickname()) == 0)
			return (it->second);
		it++;
	}
	return NULL;
}

Channel *	Server::getChannel(std::string const & name)

{
	channel_iterator it = _ChannelTable.begin();
	
	while (it != _ChannelTable.end())
	{
		if (name.compare(it->second->getName()) == 0)
			return it->second;
		it++;
	}
	return NULL;
}

std::string Server::getTime()
{
	return this->_time;
}

void	Server::reply(std::string const & message, Client * client)
{
	client->getReplyBuffer() += message;
	for (pfd_iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
		if (it->fd == client->getFd())
		{
			it->events |= POLLOUT;
			break;
		}	
}

void	Server::sendRegistrationMsg(Client * client)
{
	this->reply(RPL_WELCOME(client->getNickname(), client->getUsername(), ""), client);
	this->reply(RPL_YOURHOST(client->getNickname(),SERVER_NAME,VERSION), client);
	this->reply(RPL_CREATED(client->getNickname(), this->getTime()), client);
	this->reply(RPL_MYINFO(client->getNickname()), client);
	this->reply(RPL_MYINFO_2(client->getNickname()), client);

	std::ifstream motdFile("motd.txt");
	if (motdFile.is_open())
	{
		this->reply(RPL_MOTDSTART(), client);
		std::string	line;
		while (std::getline(motdFile, line))
			this->reply(RPL_MOTD(line), client);
		this->reply(RPL_ENDOFMOTD(), client);
		motdFile.close();
	}
	client->setWelcomeSent();
	std::cout << WHITE "Client #" << client->getFd() << " registered" RESET << std::endl;
}


Channel* Server::findChannel(const std::string& name) {
	std::map<std::string, Channel*>::iterator it = _ChannelTable.find(name);
	if (it != _ChannelTable.end())
		return it->second;
	return NULL;
}

void Server::addChannel(const std::string& name, Channel* channel) {
	if (_ChannelTable.find(name) == _ChannelTable.end())
		_ChannelTable[name] = channel;
}

void Server::removeChannel(Channel *channel) {
	if (!channel)
		return;

	std::string name = channel->getName();
	std::map<std::string, Channel*>::iterator it = _ChannelTable.find(name);
	if (it != _ChannelTable.end()) {
		delete it->second;
		_ChannelTable.erase(it);
	}
}

Client* Server::findClientByNick(const std::string& nick) {
	for (std::map<int, Client*>::iterator it = _ClientTable.begin(); it != _ClientTable.end(); ++it) {
		if (it->second->getNickname() == nick)
			return it->second;
	}
	return NULL;
}

void	Server::removeinvban(std::string nickname)
{
	for (std::map<std::string, Channel *>::iterator it = _ChannelTable.begin(); it != _ChannelTable.end(); it++)
	{
		Channel *chan = it->second;
		if (chan->checkInvit(nickname))
			chan->removeInvit(nickname);
		if (chan->checkBan(nickname))
			chan->unban(nickname);
	}
}