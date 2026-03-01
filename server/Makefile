NAME = server

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS = main.cpp \
       services/server.cpp \
       services/serverHandlers.cpp \
       services/pollManager.cpp \
       services/epollManager.cpp \
       services/connectionManager.cpp \
       infra/serverSocket.cpp \
       infra/clientSocket.cpp \
       infra/fileDescriptor.cpp \
       domain/port.cpp \
       domain/ipAddr.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
