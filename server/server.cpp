#include "includes/server.hpp"

Server::Server() {}

Server::~Server() {}

bool  Server::initialize(int Port, const std::string &IpAddr)
{
    if (!_serverSocket.initialize(Port, IpAddr))
        return (handleError("Failed to initialize socket"));
    if (!_serverSocket.setBind())
        return (handleError("Failed to bind socket"));
    if (!_serverSocket.setListen(SOMAXCONN))
        return (handleError("Failed to listen on socket"));
    
    pollfd  serverPoll;
    serverPoll.fd = _serverSocket.getPollFd();
    serverPoll.events = POLLIN;
    serverPoll.revents = 0;
    _pollFds.push_back(serverPoll);
    
    return (true);
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

    ClientSocket    client(newClient);
    if (client.isValid())
    {
        client.invalidate();
        return;
    }
    
    pollfd  clientPoll;
    clientPoll.fd = client.getPollFd();
    clientPoll.events = POLLIN;
    clientPoll.revents = 0;
    _pollFds.push_back(clientPoll);
    
    std::cout << "New client connected: fd" << newClient << std::endl;
}

void    Server::handleClientData(size_t index)
{
    char    buffer[1024];
    int     clientFd = _pollFds[index].fd;
    ClientSocket    client(clientFd);

    ssize_t  bRead = client.receiveData(buffer, sizeof(buffer));
    if (bRead <= 0)
    {
        std::cout << "Client disconnected: fd " << clientFd << std::endl;
        client.invalidate();
        _pollFds.erase(_pollFds.begin() + index);
        return;
    }

    std::cout << "Received " << bRead << " bytes: " 
    << std::string(buffer, bRead) << std::endl;
}
