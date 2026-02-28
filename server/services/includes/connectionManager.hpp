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
		std::map<int, ClientSocket*>	_clients;
		EpollManager&				_epollManager;

	public:
		explicit ConnectionManager(EpollManager& epollManager);
		~ConnectionManager();

		void	acceptNewClient(ServerSocket& serverSocket);
		void	handleClientData(int fd);
		
		size_t	getClientCount() const;
};

#endif