#include "includes/server.hpp"

Server::Server() 
: _epollManager(NULL), _connectionManager(NULL), _isValid(false) 
{}

Server::Server(const Port& port, const IpAddr& ipAddr)
: _serverSocket(port, ipAddr), _epollManager(NULL), _connectionManager(NULL), _isValid(false)
{
    _epollManager = new EpollManager();
    
    if (!_epollManager)
    {
        handleError("Failed to create event manager");
        return;
    }
    
    _connectionManager = new ConnectionManager(*_epollManager);
    if (!_connectionManager)
    {
        handleError("Failed to create connection manager");
        return;
    }
    
    if (!_serverSocket.isValid())
    {
        handleError("Failed to initialize socket");
        return;
    }
    if (!_serverSocket.setBind())
    {
        handleError("Failed to bind socket");
        return;
    }
    if (!_serverSocket.setListen(SOMAXCONN))
    {
        handleError("Failed to listen on socket");
        return;
    }
    
    _epollManager->addFd(_serverSocket.getPollFd(), POLLIN);
    _isValid = true;
}

Server::~Server()
{
    delete _connectionManager;
    delete _epollManager;
}

bool	Server::isValid() const
{
    return _isValid;
}

void	Server::run()
{
    while (true)
    {
        int ret = _epollManager->waitForEvents();

        if (ret < 0)
        {
            handleError("event manager failed");
            break;
        }
        
        if (_epollManager->hasServerEvent())
            _connectionManager->acceptNewClient(_serverSocket);
        
        std::vector<size_t> clientIndices = _epollManager->getClientEventIndices();
        for (size_t i = 0; i < clientIndices.size(); i++)
            _connectionManager->handleClientData(clientIndices[i]);
    }
}
