NAME = ft_irc

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = Commands/Authentication/Nick.cpp \
		Commands/CommandHandler.cpp \
		Commands/Authentication/Pass.cpp \
		Commands/Authentication/Register.cpp \
		Commands/Authentication/User.cpp \
		Commands/ChannelMessages/Join.cpp \
		Commands/ChannelMessages/Privmsg.cpp \
		Commands/OperatorCommands/Invite.cpp \
		Commands/OperatorCommands/Kick.cpp \
		Commands/OperatorCommands/Mode.cpp \
		Commands/OperatorCommands/Topic.cpp \
		Networking/server_init.cpp \
		Networking/server.cpp \
		Parsing/Channel.cpp \
		Parsing/Client.cpp \
		main.cpp

OBJS = $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJS}
