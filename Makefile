# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momillio <momillio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 11:34:29 by momillio          #+#    #+#              #
#    Updated: 2025/04/14 11:51:53 by momillio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= irc
CC		= c++
CFLAGS	= -Werror -Wextra -Wall -std=c++98

SRC		= main.cpp\
			srcs/Channel.class.cpp\
			srcs/Client.class.cpp\
			srcs/Invite.cpp\
			srcs/Join.cpp\
			srcs/Kick.cpp\
			srcs/Mode.cpp\
			srcs/Nick.cpp\
			srcs/ParseMessage.cpp\
			srcs/Pass.cpp\
			srcs/Privmsg.cpp\
			srcs/Server.class.cpp\
			srcs/Server.cpp\
			srcs/ServerDebug.cpp\
			srcs/ServerLoop.cpp\
			srcs/ServerUtils.cpp\
			srcs/Topic.cpp\
			srcs/User.cpp\
			srcs/Utils.cpp			
OBJECTS		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "\033[1;32mCompilation succesfull !\033[0m"

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@echo "\033[1;31mClean succesfull ! \033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31mFclean succesfull ! \033[0m"

re: fclean all

.PHONY: all re clean fclean
