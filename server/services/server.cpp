#include "includes/server.hpp"

Server::Server() 
: _eventManager(NULL), _connectionManager(NULL), _isValid(false) 
{}

Server::Server(EventType type, const Port& port, const IpAddr& ipAddr)
: _serverSocket(port, ipAddr), _eventManager(NULL), _connectionManager(NULL), _isValid(false)
{
    if (type == POLL)
        _eventManager = new PollManager();
    else if (type == EPOLL)
        _eventManager = new EpollManager();
    
    if (!_eventManager)
    {
        handleError("Failed to create event manager");
        return;
    }
    
    _connectionManager = new ConnectionManager(*_eventManager);
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
    
    _eventManager->addFd(_serverSocket.getPollFd(), POLLIN);
    _isValid = true;
}

Server::~Server()
{
    delete _connectionManager;
    delete _eventManager;
}

bool	Server::isValid() const
{
    return _isValid;
}

void	Server::run()
{
    while (true)
    {
        int ret = _eventManager->waitForEvents();

        if (ret < 0)
        {
            handleError("event manager failed");
            break;
        }
        
        if (_eventManager->hasServerEvent())
            _connectionManager->acceptNewClient(_serverSocket);
        
        std::vector<size_t> clientIndices = _eventManager->getClientEventIndices();
        for (size_t i = 0; i < clientIndices.size(); i++)
            _connectionManager->handleClientData(clientIndices[i]);
    }
}
