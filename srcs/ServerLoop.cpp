/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLoop.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:18:26 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:51:57 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

/*
	poll(struct pollfd *fds, nfds_t nfds, int timeout)
		- timeout :
			-> 0 = immediate response (non-blocking)
			-> > 0 = wait for time given
			-> -1 = wait until an event occurs
	struct pollfd { int fd, short events, short revents}
		- fd : fd to watch
		- events : events to watch
		- revents : events detected
			-> POLLIN = data ready to be read
			-> POLLOUT = ready to write without blocking
			-> POLLER = error on fd
			-> POLLHUP = disconnected or fd closed
			-> POLLNVAL = fd invalide
		- return value :
			-> Number of fd ready (> 0)
			-> 0 if timeout without events detected
			-> -1 with erno error
*/

int	Server::serverLoop()
{
	pollfd poll_srv;

	poll_srv.fd = _servSocketFd;
	poll_srv.events = POLLIN;
	poll_srv.revents = 0;

	_pollFds.push_back(poll_srv);

	while (_signal == false)
	{
		for (pfd_iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
			it->revents = 0;
		if (poll(_pollFds.data(), _pollFds.size(), -1) < 0)
		{
			std::cerr << "\nError : error while polling" << std::endl;
			return FAILURE;
		}
			
		for (pfd_iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
		{
			if (it->revents == 0)
				continue ;
			if ((it->revents & POLLIN))
			{
					if (it->fd == _servSocketFd)
					{
						createConnection();
						break ;
					}
					else
					{
						readMessage(it->fd);
						break ;
					}

			}
			if (it->revents & POLLOUT)
			{
				respondToClient(it->fd);
				break;
			}
			if ((it->revents & POLLHUP))
			{
				disconnectClient(it->fd);
				break ;
			}
		}
	}
	return SUCCESS;
}