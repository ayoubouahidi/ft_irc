NAME        = irc

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++11
INCLUDES    = -I. -I./Commands -I./Networking -I./Parsing

SRCS        = main.cpp \
			  Networking/server.cpp \
			  Networking/server_init.cpp \
			  Parsing/Client.cpp \
			  Parsing/Channel.cpp \
			  Commands/CommandHandler.cpp \
			  Commands/Invite.cpp \
			  Commands/Join.cpp \
			  Commands/Kick.cpp \
			  Commands/Mode.cpp \
			  Commands/Nick.cpp \
			  Commands/Notice.cpp \
			  Commands/Part.cpp \
			  Commands/Pass.cpp \
			  Commands/Ping.cpp \
			  Commands/Privmsg.cpp \
			  Commands/Quit.cpp \
			  Commands/Register.cpp \
			  Commands/Topic.cpp \
			  Commands/User.cpp

OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re