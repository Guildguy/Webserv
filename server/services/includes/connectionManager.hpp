#ifndef	CONNECTIONMANAGER_HPP
#define CONNECTIONMANAGER_HPP

#include "../../infra/includes/serverSocket.hpp"
#include "../../infra/includes/clientSocket.hpp"
#include "epollManager.hpp"

#include <vector>
#include <poll.h>
#include <map>
#include <unistd.h>
#include <iostream>

class	ConnectionManager
{
	private:	
		EpollManager&				_epollManager;
		std::vector<ClientSocket*>	_clients;


	public:
		explicit ConnectionManager(EpollManager& epollManager);
		~ConnectionManager();

		void	acceptNewClient(ServerSocket& serverSocket);
		ClientSocket* getClientByFd(int fd);
		void 	removeClient(int fd);
		void	handleClientData(int fd);
		
		size_t	getClientCount() const;
};

#endif