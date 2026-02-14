#include "includes/server.hpp"

Server::Server() : _isValid(false) {}

Server::Server(int Port, const std::string& IpAddr)
: _serverSocket(Port, IpAddr), _isValid(false)
{
    if (!_serverSocket.isValid())
    {
        handleError("Failed to initialize socket");
        return ;
    }
    if (!_serverSocket.setBind())
    {
        handleError("Failed to bind socket");
        return ;
    }
    if (!_serverSocket.setListen(SOMAXCONN))
    {
        handleError("Failed to listen on socket");
        return ;
    }
    
    pollfd  serverPoll;
    serverPoll.fd = _serverSocket.getPollFd();
    serverPoll.events = POLLIN;
    serverPoll.revents = 0;
    _pollFds.push_back(serverPoll);
    
    _isValid = true;
}

Server::~Server()
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        delete _clients[i];
    }
    _clients.clear();
}

bool    Server::isValid() const
{
    return (_isValid);
}

void    Server::run()
{
    while (true)
    {
        int ret = poll(_pollFds.data(), _pollFds.size(), -1);

        if (ret < 0)
        {
            handleError("poll failed");
            break;
        }
        for (size_t i = 0; i < _pollFds.size(); i++)
        {
            if (!(_pollFds[i].revents & POLLIN))
                continue;
            if (i == 0)
            {
                acceptNewClient();
                continue;
            }
            handleClientData(i);
        }
    }
}

void    Server::acceptNewClient()
{
    int newClient = _serverSocket.setAccept();
    
    if (newClient < 0)
        return ;

    ClientSocket* client = new ClientSocket(newClient);
    if (!client->isValid())
    {
        delete client;
        close(newClient);
        return ;
    }
    
    pollfd  clientPoll;
    clientPoll.fd = client->getPollFd();
    clientPoll.events = POLLIN;
    clientPoll.revents = 0;
    _pollFds.push_back(clientPoll);
    _clients.push_back(client);
    
    std::cout << "New client connected: fd " << newClient << std::endl;
}

void    Server::handleClientData(size_t index)
{
    char    buffer[1024];
    ClientSocket* client = _clients[index - 1];

    ssize_t  bRead = client->receiveData(buffer, sizeof(buffer));
    if (bRead <= 0)
    {
        std::cout << "Client disconnected: fd " << client->getPollFd() << std::endl;
        delete client;
        _clients.erase(_clients.begin() + (index - 1));
        _pollFds.erase(_pollFds.begin() + index);
        return ;
    }

    std::cout << "Received " << bRead << " bytes: " 
    << std::string(buffer, bRead);
}
