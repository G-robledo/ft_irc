/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:39:40 by momillio          #+#    #+#             */
/*   Updated: 2025/04/16 14:41:56 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"

#define MAXMEMBER 10

class Client;
class Server;
class Commands;

class Channel
{
private:
	std::string					_name;
	std::string					_topic;
	std::string					_topicSetBy;
	std::string					_key;
	size_t						_limit;

	std::set<std::string>		_banlist;
	std::set<std::string>		_invitelist;
	std::set<std::string>		_operatorList;

	std::map<int, Client*>		_memberlist;
	std::set<char>				_activeModes;

	bool						_inviteOnly;
	bool						_topicForOP;
	std::string					_creator;


	Server *					_srv;
public:
	Channel(std::string const &name, Server *srv);
	Channel(const std::string &name, const std::string &key, Server *srv);
	~Channel();

// getter
	std::string					getUsers() const;
	std::string const &			getName() const;
	std::string const &			getTopic() const;
	std::string const &			getKey() const;
	size_t						getLimit() const;
	bool						hasUser(std::string username);
	bool						hasKey() const;
	bool						hasLimit() const;
	bool						checkInvit(std::string username);
	bool						checkBan(const std::string username);
	bool						checkKey(const std::string& inputKey) const;
	bool						isOperator(std::string fd) const;
	bool const &				getInvOnly() const;
	bool const &				getTopicForOP() const;
	std::string					getModeString() const;
	size_t						getOperatorCount() const;
	size_t						getMemberListCount() const;
	std::string const &			getCreator() const ;

// setter
	void	setTopic(std::string const & topic);
	void	setKey(const std::string& key);
	void	unsetKey();
	void	setLimit(size_t limit);
	void	unsetLimit();

	void	setInvit(bool enable);
	void	setTopicForOP(bool enable);
	void	setCreator(std::string creator);

// mode
	void	setMode(char mode);
	void	unsetMode(char mode);
	bool	hasMode(char mode) const;

// user
	void	addUser(Client *client, Server *server);
	void	removeUser(Client *client);
	void	kickUser(Client *client, Server *server);

	void	addOperator(std::string nickname);
	void	removeOperator(std::string nickname);

// invit ban
	void	addInvit(std::string username);
	void	removeInvit(std::string username);
	void	isBan(Client *client, Server* server);
	void	unban(std::string nickname);

// name
	static bool isNameValid(const std::string name);


	void	broadcast(Client * client, std::string const & message);

	void giveRandomOp();


};
