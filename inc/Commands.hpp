/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:01:27 by grobledo          #+#    #+#             */
/*   Updated: 2025/04/16 14:41:14 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"

class Server;
class Client;
class Channel;

class Commands
{
public:
	static void handleNick(std::vector<std::string> params, std::string trailing, Client * client, Server *srv);
	static void handleUser(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handleJoin(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handlePrivmsg(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handleKick(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handleInvite(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handleTopic(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handleMode(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
	static void handlePass(std::vector<std::string> params, std::string trailing, Client * client , Server *srv);
};