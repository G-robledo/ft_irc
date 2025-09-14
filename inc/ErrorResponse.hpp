/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorResponse.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:23:17 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:41:22 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"

// Numeric Replies

#define ERR_NOSUCHNICK(nickname, channelname) (":" + std::string(SERVER_NAME) + " :401 " + channelname + " " + nickname + " :No such nick/channel" + CRLF)
#define ERR_NOSUCHCHANNEL(channelname) (":" + std::string(SERVER_NAME) + " 403 " + channelname + " :No such channel" + CRLF)
#define ERR_CANNOTSENDTOCHAN(channelname) (":" + std::string(SERVER_NAME) + " 404 " + channelname + " :Cannot send to channel" + CRLF)
#define ERR_TOOMANYCHANNELS(channelname) (":" + std::string(SERVER_NAME) + " 405 " + channelname + " :You have joined too many channels" + CRLF)
#define ERR_WASNOSUCHNICK(nickname) (":" + std::string(SERVER_NAME) + " 406 " + nickname + " :There was no such nickname" + CRLF)

#define ERR_NORECIPIENT(command) (":" + std::string(SERVER_NAME) + " :411 :No recipient given (" + command + ")" + CRLF)
#define ERR_NOTEXTTOSEND() (":" + std::string(SERVER_NAME) + " 412 :No text to send" + CRLF)
#define ERR_NOTOPEVEL(mask) (":" + std::string(SERVER_NAME) + " 413 " + mask + " :No toplevel domain specified" + CRLF)
#define ERR_WILDTOPLEVEL(mask) (":" + std::string(SERVER_NAME) + " 414 " + mask + " :Wildcard in toplevel domain" + CRLF)
#define ERR_BADMASK(mask) (":" + std::string(SERVER_NAME) + " 415 " + mask + " :Bad Server/host mask" + CRLF)

#define ERR_UNKNOWNCOMMAND(command) (s":" + std::string(SERVER_NAME) + " :421 " + command + " :Unknown command" + CRLF)
#define ERR_NOMOTD() (":" + std::string(SERVER_NAME) + " :422 :MOTD File is missing" + CRLF)
#define ERR_NONICKNAMEGIVEN() (":" + std::string(SERVER_NAME) + " 431 :No nickname given" + CRLF)
#define ERR_ERRONEUSNICKNAME(nickname) (":" + std::string(SERVER_NAME) + " 432 " + nickname + " :Erroneous nickname" + CRLF)
#define ERR_NICKNAMEINUSE(nickname) (":" + std::string(SERVER_NAME) + " 433 " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_USERNOTINCHANNEL(nickname, channelname) (":" + std::string(SERVER_NAME) + " 441 " + nickname + " " + channelname + " :They aren't on that channel" + CRLF)
#define ERR_NOTONCHANNEL(channelname) (":" + std::string(SERVER_NAME) + " 442 " + channelname + " :You're not on that channel" + CRLF)
#define ERR_USERONCHANNEL(username, channelname) (":" + std::string(SERVER_NAME) + " 443 " + username + " " + channelname + " :Is already on that channel" + CRLF)
#define ERR_USERSDISABLED() (":" + std::string(SERVER_NAME) + " 446 :USERS has been disabled" + CRLF)
#define ERR_NOTREGISTERED() (":" + std::string(SERVER_NAME) + " 451 :You have not registered" + CRLF)
#define ERR_NEEDMOREPARAMS(command) (":" + std::string(SERVER_NAME) + " 461 " + command + " :Not enough parameters" + CRLF)
#define ERR_ALREADYREGISTERED() (":" + std::string(SERVER_NAME) + " 462 :Unauthorized command (already registered)" + CRLF)
#define ERR_PASSWDMISMATCH() (":" + std::string(SERVER_NAME) + " 464 :Password incorrect" + CRLF)
#define ERR_YOUREBANNEDCREEP() (":" + std::string(SERVER_NAME) + " 465 :You are banned from this server" + CRLF)
#define ERR_ERRORSYNTAXE(command) (command + std::string(" :Error syntaxe") + CRLF)

// Channel errors

#define ERR_KEYSET(channelname) (":" + std::string(SERVER_NAME) + " 467 " + channelname + " :Channel key already set" + CRLF)
#define ERR_CHANNELISFULL(channelname) (":" + std::string(SERVER_NAME) + " 471 " + channelname + " :Cannot join channel (+l)" + CRLF)
#define ERR_UNKNOWNMODE(modechar, channelname) (":" + std::string(SERVER_NAME) + " 472 " + modechar + " :Is unknown mode char to me for " + channelname + CRLF)
#define ERR_INVITEONLYCHAN(channelname) (":" + std::string(SERVER_NAME) + " 473 " + channelname + " :Cannot join channel (+i)" + CRLF)
#define ERR_BANNEDFROMCHAN(channelname) (":" + std::string(SERVER_NAME) + " 474 " + channelname + " :Cannot join channel (+b)" + CRLF)
#define ERR_BADCHANNELKEY(channelname) (":" + std::string(SERVER_NAME) + " 475 " + channelname + " :Cannot join channel (+k)" + CRLF)
#define ERR_BADCHANMASK(channelname) (":" + std::string(SERVER_NAME) + " 476 " + channelname + " :Bad channel mask" + CRLF)
#define ERR_NOCHANMODES(channelname) (":" + std::string(SERVER_NAME) + " 477 " + channelname + " :Channel doesn't support modes" + CRLF)
#define ERR_BANLISTFULL(channelname) (":" + std::string(SERVER_NAME) + " 478 " + channelname + " :Channel ban list is full" + CRLF)
#define ERR_NOPRIVILEGES() (":" + std::string(SERVER_NAME) + " 481 :Permission Denied - You're not an IRC operator" + CRLF)
#define ERR_CHANOPRIVSNEEDED(channelname) (":" + std::string(SERVER_NAME) + " 482 " + channelname + " :You're not channel operator" + CRLF)
#define ERR_UNIQOPRIVSNEEDED() (":" + std::string(SERVER_NAME) + " 485 :You're not the original channel operator" + CRLF)
#define ERR_UMODEUNKNOWNFLAG() (":" + std::string(SERVER_NAME) + " 501 :Unknown MODE flag" + CRLF)

//error personnalisee
#define ERR_USERONINVLIST(username, Channelname) (":" + std::string(SERVER_NAME) + " Error " + (username) + " " + (Channelname) + " :Already in invit list" + CRLF)
#define ERR_NEEDLESSPARAMS(command) (":" + std::string(SERVER_NAME) + "  " + command + " :Too much params" + CRLF)
#define ERR_LASTCHANOP(channelname, nickname) (":" + std::string(SERVER_NAME) + "  " + channelname + " :Error " + nickname + " is the last operator of the channel" + CRLF)
#define ERR_ISCREATOR(channelname, nickname) (":" + std::string(SERVER_NAME) + "  " + channelname + " :Error " + nickname + " is creator of the channel" + CRLF)