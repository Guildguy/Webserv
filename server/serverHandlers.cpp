#include "../includes/server.hpp"

bool Server::validateServerSocketCreation()
{
  if (this->fd < 0)
    return (handleError("error: socket creation failed"));
  return (true);
}

bool  Server::handleError(const std::string& msg)
{
  perror(msg.c_str());
  return (false);
}

void Server::closeServerFD()
{
  if (this->fd != -1)
  {
    close(this->fd);
    this->fd = -1;
  }
}
