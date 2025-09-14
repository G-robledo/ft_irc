/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grobledo <grobledo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:03:54 by grobledo          #+#    #+#             */
/*   Updated: 2025/04/16 15:11:32 by grobledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

void Commands::handleJoin(std::vector<std::string> params, std::string trailing, Client *client, Server *server) \
{
	(void) trailing;

	if (params.empty()) {
		server->reply(ERR_NEEDMOREPARAMS("JOIN"), client);
		return;
	}

	if (params[0] == "0") {
		client->leaveAllChannels(server);
		return;
	}

	std::vector<std::string> channelNames = split(params[0], ',');
	std::vector<std::string> keys;
	if (params.size() > 1)
		keys = split(params[1], ',');

	for (size_t i = 0; i < channelNames.size(); ++i) {
		std::string channelName = channelNames[i];
		std::string key;

		if (i < keys.size())
			key = keys[i];
		else
			key = "";

		if (!Channel::isNameValid(channelName)) {
			server->reply(ERR_BADCHANMASK(channelName), client);
			continue;
		}

		Channel* chan = server->findChannel(channelName);
		bool isNew = false;
		if (!chan) {
			chan = new Channel(channelName, key, server);
			server->addChannel(channelName, chan);
			chan->setCreator(client->getNickname());
			isNew = true;
		}

		if (chan->checkBan(client->getNickname())) {
			server->reply(ERR_BANNEDFROMCHAN(channelName), client);
			continue;
		}

		if (chan->hasMode('i') && !chan->checkInvit(client->getNickname())) {
			server->reply(ERR_INVITEONLYCHAN(chan->getName()), client);
			continue;
		}

		if (chan->hasUser(client->getNickname())) {
			server->reply(ERR_USERONCHANNEL(client->getNickname(), channelName), client);
			continue;
		}

		if (chan->hasMode('l') && chan->getMemberListCount() >= chan->getLimit() && !chan->checkInvit(client->getNickname())) {
			server->reply(ERR_CHANNELISFULL(channelName), client);
			continue;
		}

		if (chan->hasMode('k') && chan->checkKey(key) == false) {
			server->reply(ERR_BADCHANNELKEY(channelName), client);
			continue;
		}

		chan->addUser(client, server);
		client->joinChannel(chan, server);

		if (chan->getUsers().size() == 1)
			chan->addOperator(client->getNickname());

		if (isNew == true)
			server->reply(RPL_CREATESUCCESS(), client);
		else
		{
			server->reply(RPL_JOINSUCCESS(), client);
			server->reply(RPL_TOPIC(chan->getName(), chan->getTopic()), client);
			server->reply(RPL_NAMREPLY(chan->getName(), chan->getUsers()), client);
			server->reply(RPL_ENDOFNAMES(chan->getName()), client);
		}
		if (chan->checkInvit(client->getNickname()))
			chan->removeInvit(client->getNickname());
	}
}
