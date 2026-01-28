#include "server.hpp"

bool  Server::createAndConfigServersocket()
{
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!this->validateServerSocketCreation())
    return (false);

  if (!this->configServerNonBlocking())
    return (false);
  if (!this->configServerReuseAddress())
    return (false);
  return (true);
}

bool Server::validateServerSocketCreation()
{
  if (this->fd < 0)
  {
    perror("failed to create a server socket!");
    return (false);
  }
  std::cout << "server socket created!" << std::endl;
  return (true);
}

bool Server::configServerNonBlocking()
{
  int flag = fcntl(this->fd, F_GETFL, 0);

  if (flag == -1)
  {
    perror("error: fcntl(F_GETFL)");
    close(this->fd);
    return (false);
  }

  if (fcntl(this->fd, F_SETFL, flag | O_NONBLOCK) == -1)
  {
    perror("error: fcntl(F_SETFL)");
    close(this->fd);
    return (false);
  }
  return (true);
}

bool Server::configServerReuseAddress()
{
  int opt = 0;

  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
  {
    std::cerr << "setsockopt err\n" << std::endl;
    close(this->fd);
    return (false);
  }
  return (true);
}
