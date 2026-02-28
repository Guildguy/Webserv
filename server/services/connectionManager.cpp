#include "includes/connectionManager.hpp"

ConnectionManager::ConnectionManager(EpollManager& epollManager) :
_epollManager(epollManager),
_clients(1024, (ClientSocket*)NULL)
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
	if (static_cast<size_t>(newClient) >= _clients.size())
        _clients.resize(newClient + 128, (ClientSocket*)NULL);

    _clients[newClient] = client;
	
	std::cout << "New client connected: fd " << newClient << std::endl;
}

void ConnectionManager::handleClientData(int fd)
{
    ClientSocket* client = _clients[fd];
    
    if (client == NULL)
        return;

    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = client->receiveData(buffer, sizeof(buffer) - 1);
    
    if (bytesRead <= 0)
    {
        _epollManager.removeFd(fd);
        delete client;
        _clients[fd] = NULL;
        return;
    }

    std::cout << "Data from fd " << fd << ": " << buffer << std::endl;
    
    // Teste de resposta
    sendTestHttpResponse(*client);
    shutdown(fd, SHUT_WR);
    
    std::cout << "Client disconnected: fd " << fd << std::endl;
    
    _epollManager.removeFd(fd);
    delete client;
    _clients[fd] = NULL;
}

ClientSocket* ConnectionManager::getClientByFd(int fd)
{
    if (fd < 0)
        return (NULL);
    if (static_cast<size_t>(fd) >= _clients.size())
        return (NULL);
    return (_clients[fd]);
}

void ConnectionManager::removeClient(int fd)
{
    std::cout << "Closing connection on fd: " << fd << std::endl;
    _epollManager.removeFd(fd);
    delete _clients[fd];
    _clients[fd] = NULL;
}


size_t	ConnectionManager::getClientCount() const
{
	return (_clients.size());
}