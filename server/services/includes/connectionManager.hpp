#ifndef	CONNECTIONMANAGER_HPP
#define CONNECTIONMANAGER_HPP

#include "../../infra/includes/serverSocket.hpp"
#include "../../infra/includes/clientSocket.hpp"
#include "eventManager.hpp"
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <iostream>

class	ConnectionManager
{
	private:	
		std::vector<ClientSocket*>	_clients;
		EventManager&				_eventManager;

	public:
		explicit ConnectionManager(EventManager& eventManager);
		~ConnectionManager();

		void	acceptNewClient(ServerSocket& serverSocket);
		void	handleClientData(size_t index);
		
		size_t	getClientCount() const;
};

#endif