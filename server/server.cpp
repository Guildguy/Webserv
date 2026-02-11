#include "includes/server.hpp"

Server::Server() {}

Server::~Server() {}

bool  Server::initializeServer(int Port, const std::string &IP)
{
    if (!this->setupSocket())
        return (false);
    if (!this->ConfigServerAddress(Port, IP))
        return (closeServerFD());
    if (!this->bindServerSocket())
        return (closeServerFD());
    if (!this->socketListener())
        return (closeServerFD());
    if (!this->configServerPoll())
        return (closeServerFD());
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
    int newClient = accept(this->fd, 0, 0);
    

    if (newClient == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return (-1);
        handleError("accept failed");
        return (-1);
    }
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

bool    Server::setupSocket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    _server_fd = FileDescriptor(fd);

    if (!_server_fd.isValid())
        return (handleError("error: socket creation failed"));
    if (!_server_fd.setNonBlocking())
        return (handleError("error: setNonBlocking failed"));
    
    if (!this->configServerReuseAddress())
        return (closeServerFD());
    return (true);
}


bool Server::configServerReuseAddress()
{
    int opt = 1;

    if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
        return (handleError("error: setsockopt(SO_REUSEADDR) failed"));
    return (true);
}

bool Server::ConfigServerAddress(int Port, const std::string& IP)
{
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(Port);
    
    if (IP == "0.0.0.0" || IP.empty())
    {
        saddr.sin_addr.s_addr = INADDR_ANY;
        return (true);
    }
    
    in_addr_t addr = inet_addr(IP.c_str());
    if (addr == INADDR_NONE)
        return (handleError("error: invalid IP address"));
    
    saddr.sin_addr.s_addr = addr;
    return (true);
}

bool  Server::bindServerSocket()
{
    if (bind(this->fd, (struct sockaddr*)&this->saddr, sizeof(this->saddr)) < 0)
        return (handleError("error: bind failed"));
    return (true);
}

bool  Server::socketListener()
{
    if (listen(this->fd, SOMAXCONN) < 0)
        return (handleError("Error: Socket cannot listen!"));
    return (true);
}

bool	Server::configServerPoll()
{
	this->serverPoll.fd = this->fd;
	this->serverPoll.events = POLLIN;
	this->serverPoll.revents = 0;
	return (true);
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