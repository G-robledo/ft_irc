/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 08:39:27 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 10:44:26 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"

class Server;
class Commands;
class Channel;

class Client
{
private:
	int 								_fd;
	std::string							_ipAdd;
	std::string							_nickname;
	std::string							_username;
	std::string							_realname;
	std::string							_replybuffer;
	std::string							_readBuffer;
	std::map<std::string, Channel *>	_channelList;
	
	bool		_isAuthentified; 
	bool		_hasEnteredPass;
	bool		_welcomeSent;

	Server *	_srv;
public:
	Client(Server *srv);
	~Client();

	void	setFd(int fd);
	void	setNickname(std::string const & nick);
	void	setUsername(std::string const & user);
	void	setRealname(std::string const & realName);
	void	setIpAdd(std::string ipAdd);
	void	setIsAuthentified();
	void	setHasEnteredPass();
	void	setWelcomeSent();

	int					getFd() const;
	std::string const & getIpAdd() const;
	std::string const & getNickname() const;
	std::string const & getUsername() const;
	std::string const & getRealname() const;
	std::string	&		getReplyBuffer();
	std::string &		getReadBuffer();
	bool				getIsAuthentified() const;
	bool				getHasEnteredPass() const;
	bool				getWelcomeSent() const;
	std::string const	getPrefix() const;

	bool		HasRequiredInfos();
	void		joinChannel(Channel * channel, Server *server);
	void		leaveAllChannels(Server *server);
	void		removeChannel(const std::string& channelName);
};
