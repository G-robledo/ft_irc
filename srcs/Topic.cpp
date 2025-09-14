/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:17:28 by grobledo          #+#    #+#             */
/*   Updated: 2025/04/16 14:46:51 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Irc.hpp"

void Commands::handleTopic(std::vector<std::string> param, std::string trailing, Client* client, Server* server)
{
	if (param.empty()) {
		server->reply(ERR_NEEDMOREPARAMS("TOPIC"), client);
		return;
	}

	std::string channelname = param[0];
	Channel* channel = server->findChannel(channelname);

	if (!channel) {
		server->reply(ERR_NOSUCHCHANNEL(channelname), client);
		return;
	}

	if (!channel->hasUser(client->getNickname())) {
		server->reply(ERR_NOTONCHANNEL(channelname), client);
		return;
	}

	if (trailing.empty() && param.size() == 1) {
		std::string topic = channel->getTopic();
		if (topic.empty())
			server->reply(RPL_NOTOPIC(channelname), client);
		else
			server->reply(RPL_TOPIC(channelname, topic), client);
		return;
	}

	if (channel->hasMode('t') && !channel->isOperator(client->getNickname())) {
		server->reply(ERR_CHANOPRIVSNEEDED(channelname), client);
		return;
	}

	if (trailing.empty()) {
		channel->setTopic("");
	} else {
		channel->setTopic(trailing);
	}
}

