/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:13:57 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 16:14:16 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

int	Server::createConnection()
{
	int fd;

	memset(&_clientAddr, 0, sizeof(_clientAddr));
	socklen_t	addrLen = sizeof (_clientAddr);

	
	fd = accept(_servSocketFd, (struct sockaddr *)&_clientAddr, &addrLen);
	if (fd < 0)
	{
		std::cerr << "Error : accept failed" << std::endl;
		close(_servSocketFd);
		return FAILURE;
	}

	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error : setting socket_client to non-blocking I/O failed" << std::endl;
		return FAILURE;
	}
	if (_pollFds.size() - 1 < MAX_CLIENTS)
		createClient(fd);
	else
		std::cout << RED "Too many connections" RESET << std::endl;
	
	std::cout << WHITE "Client connected" RESET << std::endl;
	return SUCCESS;
}

int	Server::createClient(int fd)
{
	Client *	client = new Client(this);
	pollfd	poll_client;
	
	poll_client.fd = fd;
	poll_client.events = POLLIN;
	poll_client.revents = 0;
	_pollFds.push_back(poll_client);
	
	client->setFd(fd);
	client->setIpAdd(inet_ntoa(_clientAddr.sin_addr));
	_ClientTable.insert(std::make_pair(fd, client));

	std::cout << WHITE "Server added client #" << client->getFd() << " successfully" RESET << std::endl;

	return SUCCESS;
}

void	Server::disconnectClient(int fd)
{
	Client * client = _ClientTable.at(fd);

	if (!client)
		return ;
	
	client->leaveAllChannels(this);
	
	client_iterator  it = _ClientTable.find(fd);
	if (it != _ClientTable.end())
	{
		delete it->second;
		_ClientTable.erase(it);
		std::cout << WHITE "Client #" << fd << " deleted" RESET << std::endl;
	}
	else
		std::cout << RED << "Client not found" << std::endl;

	close(fd);
	
	for (pfd_iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
		if (it->fd == fd)
		{
			_pollFds.erase(it);	
			break;
		}
	std::cout << WHITE "Client #" << fd << " disconnected" RESET << std::endl;
}

void	Server::readMessage(int fd)
{
	ssize_t	read_bytes;
	char	buffer[BUFFER_SIZE];
	Client * client = _ClientTable.at(fd);

	memset(buffer, 0, sizeof(buffer));
	read_bytes = recv(fd, buffer, BUFFER_SIZE - 1, 0);

	if (read_bytes < 0)
	{
		std::cout << RED "Error : failed recv" RESET << std::endl; 
		return ;
	}
	else if (read_bytes == 0)
	{
		disconnectClient(fd);
		return ;
	}
	else
	{
	client->getReadBuffer().append(buffer);
	
	std::size_t pos = client->getReadBuffer().find("\r\n");
	std::size_t pos2 = client->getReadBuffer().find("\n");
	if (pos == std::string::npos && pos2 == std::string::npos)
		return ;

	this->parseMessage(client->getReadBuffer(), client);
	client->getReadBuffer().clear();
	}
}

int	Server::respondToClient(int fd)
{
	Client * client = _ClientTable.at(fd);
	if (!client)
		std::cerr << "Client not found" << std::endl;
	if (client->getReplyBuffer().empty())
		return SUCCESS;
	if (send(client->getFd(), client->getReplyBuffer().c_str(), client->getReplyBuffer().size(), 0) <= 0)
	{
		std::cerr << "Error : send failed" << std::endl;
		disconnectClient(client->getFd());
		return FAILURE;
	}
	client->getReplyBuffer().clear();
	for (pfd_iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
		if (it->fd == client->getFd())
		{
			it->events &= ~POLLOUT;
			break ;
		}
	return SUCCESS;
}

