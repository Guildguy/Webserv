#ifndef  SERVER_HPP
#define  SERVER_HPP

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <vector>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class  Server
{
    private:
        int					fd;
        struct  sockaddr_in	saddr;
        struct  pollfd		serverPoll;

        bool	configServerNonBlocking();
        bool	configServerReuseAddress();
        bool	ConfigServerAddress(int Port, const std::string& IP);
        bool	bindServerSocket();
        bool	socketListener();
		bool	configServerPoll();
        
        bool	handleError(const std::string& msg);
        bool	validateServerSocketCreation();
        bool	closeServerFD();

		int		acceptNewClient(std::vector<pollfd>& fds);
		bool    configClientNonBlocking(int newClient);
		bool    configClientPoll(std::vector<pollfd>& fds, int newClient);

    public:
        Server();
        ~Server();

        bool	setupSocket();
        bool	initializeServer(int Port, const std::string &IP);
		void	run();
    
};

#endif

//ncdu