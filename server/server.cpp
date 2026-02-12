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
    std::vector<pollfd> fds;

    fds.push_back(serverPoll);

    while (true)
    {
        int ret = poll(fds.data(), fds.size(), -1);

        if (ret < 0)
        {
            handleError("poll failed");
            break;
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (!(fds[i].revents & POLLIN))
                continue;
            if (i == 0)
            {
                acceptNewClient(fds);
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

    ssize_t  bRead = recv(clientFd, buffer, sizeof(buffer), 0);
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

int    Server::acceptNewClient(std::vector<pollfd>& fds)
{
    int newClient = -serverSocket.setAccept();
    
    if (newClient < 0)
        return ;
    
    if (!configClientNonBlocking(newClient))
    {
        close(newClient);
        return (-1);
    }
    if (!configClientPoll(fds, newClient))
    {
        close(newClient);
        return (-1);
    }
    return (newClient);
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