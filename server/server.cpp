#include "../includes/server.hpp"

Server::Server() : fd(-1) {}

Server::~Server()
{
    if (this->fd != -1)
        closeServerFD();
}

bool  Server::initializeServer(int Port, const std::string &IP)
{
    if (!this->createAndPreConfigServerSocket())
        return (false);
    if (!this->ConfigServerAddress(Port, IP))
        return (closeServerFD());
    if (!this->bindServerSocket())
        return (closeServerFD());
    if (!this->socketListener())
        return (closeServerFD());
    return (true);
}

bool  Server::createAndPreConfigServerSocket()
{
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!this->validateServerSocketCreation())
        return (false);

    if (!this->configServerNonBlocking())
        return (closeServerFD());
    if (!this->configServerReuseAddress())
        return (closeServerFD());
    return (true);
}

bool Server::configServerNonBlocking()
{
    int flag = fcntl(this->fd, F_GETFL, 0);

    if (flag == -1)
        return (handleError("error: fcntl(F_GETFL) failed"));
    if (fcntl(this->fd, F_SETFL, flag | O_NONBLOCK) == -1)
        return (handleError("error: fcntl(F_SETFL) failed"));
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

bool	Server::configPoll()
{
	this->pollfd_server.fd = this->fd;
	this->pollfd_server.events = POLLIN;
	this->pollfd_server.revents = 0;
	return (true);
}
