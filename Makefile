NAME = irc

CXX = c++ -g

CXXFLAGS = -Wall -Werror -Wextra

SRCs = main.cpp\
		server.cpp\

OBJs = $(SRCs:.cpp=.o)

$(NAME) : $(OBJs)
	$(CXX) $(CXXFLAGS) $(OBJs) -o $(NAME)

clean : 
	rm -rf $(OBJs)

fclean : clean
	rm -rf $(NAME)

re : $(fclean) $(NAME)