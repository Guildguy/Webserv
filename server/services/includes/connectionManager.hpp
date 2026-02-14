#ifndef	CONNECTIONMANAGER_HPP
#define CONNECTIONMANAGER_HPP

#include "../../infra/includes/serverSocket.hpp"
#include "../../infra/includes/clientSocket.hpp"
#include "pollManager.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>

class	ConnectionManager
{
	private:	
		std::vector<ClientSocket*>	_clients;
		PollManager&				_pollManager;

	public:
		explicit ConnectionManager(PollManager& pollManager);
		~ConnectionManager();

		void	acceptNewClient(ServerSocket& serverSocket);
		void	handleClientData(size_t index);
		
		size_t	getClientCount() const;
};

#endif