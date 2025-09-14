/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:45:02 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:23 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

void	Channel::broadcast(Client * client, std::string const & message)
{
	std::map<int, Client *>::iterator it = _memberlist.begin();
	while (it != _memberlist.end())
	{
		if (it->second->getNickname() == client->getNickname())
		{
			it++;
			continue ;
		}
		else
		{
			_srv->reply(message, it->second);
			it++;	
		}
	}
}

bool	isValidParam(std::vector<std::string> & param, std::string & trailing, Client * client, Server * srv)
{
	if (param.empty())
	{
		srv->reply(ERR_NORECIPIENT("PRIVMSG"), client);
		return false;
	}
	if (param.size() != 1)
	{
		srv->reply(ERR_ERRORSYNTAXE("PRIVMSG"), client);
		return false;	
	}
	if (trailing.empty())
	{
		srv->reply(ERR_NOTEXTTOSEND(), client);
		return false;
	}
	return true;
}

void Commands::handlePrivmsg(std::vector<std::string> param, std::string trailing, Client * client, Server *srv)
{
	(void)client;
	(void)srv;
	if (!isValidParam(param, trailing, client, srv))
		return ;
	
	std::string arg(param[0]);

	if (arg[0] == '#')
	{
		Channel * channel = srv->getChannel(arg);
		if (channel == NULL)
		{
			srv->reply(ERR_NOSUCHNICK("",arg), client);
			return ;
		}
		if (!channel->hasUser(client->getNickname()))
		{
			srv->reply(ERR_CANNOTSENDTOCHAN(channel->getName()), client);
			return ;
		}
		std::string message = client->getPrefix() + " PRIVMSG " + channel->getName() + " :" + trailing + CRLF;
		channel->broadcast(client, message);
	}
	else
	{
		std::string message = client->getPrefix() + " PRIVMSG :" + trailing + CRLF;
		Client * target = srv->getClient(arg);
		if (target == NULL)
		{
			srv->reply(ERR_NOSUCHNICK(arg, ""), client);
			return ;
		}
		else
			srv->reply(message, target);			
	}
}