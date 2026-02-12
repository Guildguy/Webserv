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
#include "serverSocket.hpp"
#include "clientSocket.hpp"

class  Server
{
    private:
        ServerSocket                    _serverSocket;
        std::vector<pollfd>             _pollFds;
        
		void	acceptNewClient();
		int    	handleClientData(std::vector<pollfd>& fds, size_t index);

        bool	handleError(const std::string& msg);
        bool	closeServerFD();

    public:
        Server();
        ~Server();

        bool	initialize(int Port, const std::string &IP);
		void	run();
    
};

#endif

//ncdu