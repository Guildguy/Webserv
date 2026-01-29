#include "server.hpp"

Server::Server() : fd(-1) {}

Server::~Server()
{
  if (this->fd != -1)
    closeServerFD();
}

bool  Server::createAndConfigServersocket()
{
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!this->validateServerSocketCreation())
    return (false);

  if (!this->configServerNonBlocking())
  {
    closeServerFD();
    return (false);
  }
  if (!this->configServerReuseAddress())
  {
    closeServerFD();
    return (false);
  }
  return (true);
}

bool  Server::handleError(const std::string& msg)
{
  perror(msg.c_str());
  return (false);
}

bool Server::validateServerSocketCreation()
{
  if (this->fd < 0)
    return (handleError("error: socket creation failed"));
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

void Server::closeServerFD()
{
  if (this->fd != -1)
  {
    close(this->fd);
    this->fd = -1;
  }
}

bool Server::ConfigServerAddress(int Port, const std::string& IP)

bool  Server::bindServerSocket()
{
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(8080);
  saddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(this->fd, (struct sockaddr*)&this->saddr, sizeof(this->saddr)) < 0)
    return (handleError("error: bind failed"));
  return (true);
}