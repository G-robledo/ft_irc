/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grobledo <grobledo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 08:44:23 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 12:43:01 by grobledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"


class Client;
class ParsedCommand;
class Commands;
class Channel;

class Server
{
	typedef std::vector<struct pollfd>::iterator		pfd_iterator;
	typedef std::map<int, Client *>::iterator			client_iterator;
	typedef std::map<std::string, Channel *>::iterator	channel_iterator;
	
private:
	int 										_servSocketFd;
	int											_port;
	std::string 								_password;
	std::string									_time;
	struct addrinfo								_hints;
	struct addrinfo *							_infos;
	struct sockaddr_in							_clientAddr;
	
	std::map<int, Client *>						_ClientTable;
	std::map<std::string, Channel *>			_ChannelTable;
	std::vector<struct pollfd>					_pollFds;

	static bool									_signal;
	Server() {}
public:
	Server(std::string const & port, std::string const & password, struct tm * timeinfo);
	~Server();

	int					getPort() const;
	int 				getSocketFd() const;
	std::string const & getPassword() const;
	Client * 			getClient(std::string const & nickname);
	Channel *			getChannel(std::string const & name);
	std::string			getTime();

	void	setPort(int port);
	void	setPassword(std::string password);
	void	setServSockedFd(int socket);
	void	setTime(struct tm * timeinfo);

	int			serverInit(char  *port);
	int			serverLoop();
	int			createConnection();
	int			createClient(int fd);
	int			respondToClient(int fd);
	void		readMessage(int fd);
	void		parseMessage(const std::string &line, Client * client);
	void		disconnectClient(int fd);
	void		sendRegistrationMsg(Client * client);
	void		reply(std::string const & msg, Client * client);
	static void	handeSignal(int signum);

	
	void		printServInit();
	void		printClientTable();
	void		printPollTable();
	
	Channel*	findChannel(const std::string& name);
	Client*		findClientByNick(const std::string& nick);
	void		addChannel(const std::string& name, Channel* channel);
	void		removeChannel(Channel *chan);
	void		removeinvban(std::string nickname);


};
