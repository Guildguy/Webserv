#include "includes/connectionManager.hpp"

ConnectionManager::ConnectionManager(PollManager& pollManager)
: _pollManager(pollManager)
{}

ConnectionManager::~ConnectionManager()
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		delete _clients[i];
	}
	_clients.clear();
}

void	ConnectionManager::acceptNewClient(ServerSocket& serverSocket)
{
	int newClient = serverSocket.setAccept();

	if (newClient < 0)
		return;
	
	ClientSocket* client = new ClientSocket(newClient);
	if (!client->isValid())
	{
		delete client;
		close(newClient);
		return;
	}
	
	_pollManager.addFd(client->getPollFd(), POLLIN);
	_clients.push_back(client);
	
	std::cout << "New client connected: fd " << newClient << std::endl;
}

void	ConnectionManager::handleClientData(size_t index)
{
	if (index == 0 || index > _clients.size())
		return;
	
	char	buffer[1024];
	ClientSocket* client = _clients[index - 1];

	ssize_t	bRead = client->receiveData(buffer, sizeof(buffer));
	if (bRead <= 0)
	{
		std::cout << "Client disconnected: fd " << client->getPollFd() << std::endl;
		delete client;
		_clients.erase(_clients.begin() + (index - 1));
		_pollManager.removeFd(index);
		return;
	}

	std::cout << "Received " << bRead << " bytes: " 
	<< std::string(buffer, bRead);
}

size_t	ConnectionManager::getClientCount() const
{
	return _clients.size();
}