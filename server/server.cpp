#include "includes/server.hpp"

Server::Server() {}

Server::~Server() {}

bool  Server::initialize(int Port, const std::string &IpAddr)
{
    if (!_serverSocket.initialize(Port, IpAddr))
        return (handleError("Failed to initialize socket"));
    if (!_serverSocket.setBind())
        return (handleError("Failed to bind socket"))
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
            handleClientData(fds, i);
        }
    }
}

int    Server::handleClientData(std::vector<pollfd>& fds, size_t index)
{
    char    buffer[1024];
    int     clientFd = fds[index].fd;
    ClientSocket    client(clientFd);

    ssize_t  bRead = client.receiveData(buffer, sizeof(buffer));
    if (bRead == 0)
    {
        close(clientFd);
        fds.erase(fds.begin() + index);
        return (0);
    }
    if (bRead < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
                return (-1);
        close(clientFd);
        fds.erase(fds.begin() + index);
        return (-1);
    }

    std::cout << "Received " << bRead << " bytes: " 
    << std::string(buffer, bRead) << std::endl;
    return (bRead);
}

void    Server::acceptNewClient()
{
    int newClient = _serverSocket.setAccept();
    
    if (newClient < 0)
        return ;

    ClientSocket    client(clientFd);
    if (client.isValid())
    {
        client.invalidate();
        return;
    }
    
    pollfd  clientPoll;
    clientPoll.fd = client.getPollFd();
    clientPoll.events = POLLIN;
    clientPoll.revents = 0;
    fds.push_back(clientPoll);
    
    std::cout << "New client connected: fd" << clientFd << std::endl;
}

/*********************** CLIENT ************************* */

bool    Server::configClientNonBlocking(int newClient)
{
    int flag = fcntl(newClient, F_GETFL, 0);
    if (flag == -1)
        return (handleError("error: fcntl(F_GETFL) failed"));
    if (fcntl(newClient, F_SETFL, flag | O_NONBLOCK) == -1)
        return (handleError("error: fcntl(F_SETFL) failed"));
    return (true);
}

bool    Server::configClientPoll(std::vector<pollfd>& fds, int newClient)
{
    pollfd  clientPoll;

    clientPoll.fd = newClient;
    clientPoll.events = POLLIN;
    clientPoll.revents = 0;
    fds.push_back(clientPoll);
    return(true);
}