/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdRresponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:14:29 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:31:43 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"
	// Welcome messages
	#define RPL_WELCOME(nickname, username, hostname) (std::string(":" + std::string(SERVER_NAME) + " 001 " + nickname + " :Welcome to the Internet Relay Network ") + nickname + "!" + username + "@" + hostname + CRLF)
	#define RPL_YOURHOST(nickname, servername, version) (std::string(":" + std::string(SERVER_NAME) + " 002 " + nickname + " :Your host is ") + servername + ", running version " + version + CRLF)
	#define RPL_CREATED(nickname, creationdate) (std::string(":" + std::string(SERVER_NAME) + " 003 " + nickname + " :This server was created ") + creationdate + CRLF)
	#define RPL_MYINFO(nickname) (std::string(":" + std::string(SERVER_NAME) + " 004 " + nickname + " :RFC2812 CHANTYPES=# CHANMODES=i,t,k,o,l" + CRLF))
	#define RPL_MYINFO_2(nickname) (std::string(":" + std::string(SERVER_NAME) + " 004 " + nickname + " :CHANNELLEN=50 NICKLEN=15" + CRLF))
	// Channel modes
	#define RPL_CHANNELMODEIS(channelname, mode, modeparams) (std::string(":" + std::string(SERVER_NAME) + " 324 ") + channelname + " " + mode + " " + modeparams + CRLF)
	#define RPL_UNIQOPI(channelname, nickname) (std::string(":" + std::string(SERVER_NAME) + " 325 ") + channelname + " " + nickname + CRLF)
	#define RPL_NOTOPIC(channelname) (std::string(":" + std::string(SERVER_NAME) + " :331 ") + channelname + " :No topic is set" + CRLF)
	#define RPL_TOPIC(channelname, topic) (std::string(":" + std::string(SERVER_NAME) + " :332 ") + channelname + " :" + topic + CRLF)
	#define RPL_INVITING(channelname, nickname) (std::string(":" + std::string(SERVER_NAME) + " 341 ") + channelname + " " + nickname + CRLF)
	#define RPL_INVITELIST(channelname, invitemask) (std::string(":" + std::string(SERVER_NAME) + " 346 ") + channelname + " " + invitemask + CRLF)
	#define RPL_ENDOFINVITELIST(channelname) (std::string(":" + std::string(SERVER_NAME) + " 347 ") + channelname + " :End of channel invite list" + CRLF)
	#define RPL_BANLIST(channelname, banmask) (std::string(":" + std::string(SERVER_NAME) + " 367 ") + channelname + " " + banmask + CRLF)
	#define RPL_ENDOFBANLIST(channelname) (std::string(":" + std::string(SERVER_NAME) + " 368 ") + channelname + " :End of channel ban list" + CRLF)
	
	// MOTD replies
	#define RPL_MOTDSTART() (std::string(":" + std::string(SERVER_NAME) + " 375 :- ") +  + "************************ MESSAGE OF THE DAY **************************" + CRLF)
	#define RPL_MOTD(text) (std::string(":" + std::string(SERVER_NAME) + " 372 :- ") + text + CRLF)
	#define RPL_ENDOFMOTD() (std::string(":" + std::string(SERVER_NAME) + " 376 :End of MOTD command") + CRLF)
	
	// Operator
	#define RPL_YOUREOPER() (std::string(":" + std::string(SERVER_NAME) + " 381 :You are now an IRC operator") + CRLF)
	
	// Retry
	#define RPL_TRYAGAIN(command) (std::string(":" + std::string(SERVER_NAME) + " 263 ") + command + " :Please wait a while and try again" + CRLF)
	
	//Test
	#define RPL_JOINSUCCESS() (std::string(":" + std::string(SERVER_NAME) + " :You succefully joined a channel") + CRLF)
	#define RPL_KICKSUCCESS() (std::string(":" + std::string(SERVER_NAME) + " :You succefully kicked user") + CRLF)
	#define RPL_CREATESUCCESS() (std::string(":" + std::string(SERVER_NAME) + " :You succefully created a channel") + CRLF)
	#define RPL_NAMREPLY(channelname, userlist) (std::string(":" + std::string(SERVER_NAME) + " " + std::string(channelname) + " :" + std::string(userlist) + std::string(CRLF)))
	#define RPL_ENDOFNAMES(channelname) (std::string(":" + std::string(SERVER_NAME) + " " + channelname + " :End of NAMES list" + CRLF))
	#define RPL_KICKMESSAGE(prefix, channelname, targetnick, comment) (std::string(":" + std::string(SERVER_NAME) + " KICK " + channelname + " " + targetnick + " :" + comment + CRLF))

	