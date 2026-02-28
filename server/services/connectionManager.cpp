#include "includes/connectionManager.hpp"

ConnectionManager::ConnectionManager(EpollManager& epollManager)
: _epollManager(epollManager)
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
	
	_epollManager.addFd(newClient, POLLIN);
	_clients[newClient] = client;
	
	std::cout << "New client connected: fd " << newClient << std::endl;
}

void	ConnectionManager::handleClientData(int fd)
{
	std::map<int, ClientSocket*>::iterator it = _clients.find(fd);

	if (it == _clients.end())
		return;
	
	ClientSocket* client = it->second;
	char	buffer[1024];
	
	ssize_t	bRead = client->receiveData(buffer, sizeof(buffer));
	if (bRead <= 0)
	{
		std::cout << "Client disconnected: fd " << fd << std::endl;
		_epollManager.removeFd(fd);
		delete client;
		_clients.erase(it);
		return;
	}

	std::cout << "Received " << bRead << " bytes: " 
	<< fd << std::endl;
}

size_t	ConnectionManager::getClientCount() const
{
	return (_clients.size());
}