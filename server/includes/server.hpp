#ifndef  SERVER_HPP
#define  SERVER_HPP

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <cstdlib>
#include <cerrno>
#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "fileDescriptor.hpp"
#include "serverSocket.hpp"

class  Server
{
    private:
        FileDescriptor      _serverSocket;
        struct  sockaddr_in	saddr;
        struct  pollfd		serverPoll;

        bool	bindServerSocket();
        bool	socketListener();
		bool	configServerPoll();
        
        bool	handleError(const std::string& msg);
        bool	closeServerFD();

		int		acceptNewClient(std::vector<pollfd>& fds);
		int    	handleClientData(std::vector<pollfd>& fds, size_t index);
		bool    configClientNonBlocking(int newClient);
		bool    configClientPoll(std::vector<pollfd>& fds, int newClient);

    public:
        Server();
        ~Server();

        bool	initialize(int Port, const std::string &IP);
		void	run();
    
};

#endif

//ncdu