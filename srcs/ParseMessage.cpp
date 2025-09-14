/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:00:47 by grobledo          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:09 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

static void	initCommandTable(std::map<std::string,void(*)(std::vector<std::string>, std::string, Client *, Server *)> & commandetable)
{
	commandetable["NICK"]    = Commands::handleNick;
	commandetable["USER"]    = Commands::handleUser;
	commandetable["JOIN"]    = Commands::handleJoin;
	commandetable["PRIVMSG"] = Commands::handlePrivmsg;
	commandetable["KICK"]    = Commands::handleKick;
	commandetable["INVITE"]  = Commands::handleInvite;
	commandetable["TOPIC"]   = Commands::handleTopic;
	commandetable["MODE"]    = Commands::handleMode;
	commandetable["PASS"]	 = Commands::handlePass;
}


static int	parseCommand(std::string const & message, std::vector<std::string> & params, std::string & command, std::string & trailing)
{
	std::string buffer = message;
	std::string token;
	size_t pos = 0;

	// 1. Trailing (start by " :")
	pos = buffer.find(" :");
	if (pos != std::string::npos) {
		trailing = buffer.substr(pos + 2);
		buffer = buffer.substr(0, pos);
		trailing.erase(std::remove(trailing.begin(), trailing.end(), '\r'), trailing.end());
		trailing.erase(std::remove(trailing.begin(), trailing.end(), '\n'), trailing.end());
	}

	// 2. Commands + parameters
	std::istringstream stream(buffer);
	bool first = true;
	while (stream >> token) {
		if (first) {
			command = token;
			first = false;
		} 
		else {
			params.push_back(token);
		}
	}
	return SUCCESS;
}

void Server::parseMessage(const std::string & message, Client *client) 
{
	std::vector<std::string> params;
	std::string command;
	std::string trailing;

	if(parseCommand(message, params, command, trailing) == FAILURE)
		return;
	std::map<std::string, void(*)(std::vector<std::string>, std::string, Client *, Server *)> commandetable;
	
	initCommandTable(commandetable);
	std::transform(command.begin(), command.end(), command.begin(), ::toupper);
	std::map<std::string, void(*)(std::vector<std::string>, std::string, Client *, Server *)>::iterator it = commandetable.find(command);
	if (it == commandetable.end())
		return;

	if (client->getIsAuthentified() == false)
	{
		if (client->getHasEnteredPass() == false)
		{
			if (command != "PASS")
			{
				this->reply("Error :Password required\r\n", client);
				return ;
			}
			it->second(params, trailing, client, this);
			return;
		}
		else if (command != "NICK" && command != "USER")
		{
			this->reply("Error :Nickname and username required\r\n", client);
			return ;
		}
		it->second(params, trailing, client, this);
		if (client->HasRequiredInfos())
			client->setIsAuthentified();			
		return;
	}
	else
		it->second(params, trailing, client, this);
}

