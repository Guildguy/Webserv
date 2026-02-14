#include "includes/server.hpp"

Server::Server() 
: _connectionManager(_pollManager), _isValid(false) 
{}

Server::Server(const Port& port, const IpAddr& ipAddr)
: _serverSocket(port, ipAddr), _connectionManager(_pollManager), _isValid(false)
{
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
    
    _pollManager.addFd(_serverSocket.getPollFd(), POLLIN);
    _isValid = true;
}

Server::~Server() {}

bool	Server::isValid() const
{
    return _isValid;
}

void	Server::run()
{
    while (true)
    {
        int ret = _pollManager.waitForEvents();

        if (ret < 0)
        {
            handleError("poll failed");
            break;
        }
        
        if (_pollManager.hasServerEvent())
            _connectionManager.acceptNewClient(_serverSocket);
        
        std::vector<size_t> clientIndices = _pollManager.getClientEventIndices();
        for (size_t i = 0; i < clientIndices.size(); i++)
            _connectionManager.handleClientData(clientIndices[i]);
    }
}
