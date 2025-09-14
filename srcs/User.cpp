/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:48:19 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:37:28 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

void Commands::handleUser(std::vector<std::string> param, std::string trailing, Client * client, Server *srv)
{
	(void)srv;
	if (param.size() < 3 || trailing.empty())
	{
		srv->reply(ERR_NEEDMOREPARAMS("USER"), client);
		return ;
	}
	else if (param[1] != "0" || param[2] != "*")
		{
			srv->reply(ERR_ERRORSYNTAXE("USER"), client);
			return ;
		}
	else if (client->getIsAuthentified())
	{
		srv->reply(ERR_ALREADYREGISTERED(), client);
		return ;
	}
	client->setUsername(param[0]);
	client->setRealname(trailing);
}