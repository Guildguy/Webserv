#include "server.hpp"

void  Server::createAndConfigServersocket()
{
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  validateServerSocketCreation();

  configServerNonBlocking();
  configServerReuseAddress();
}

void Server::validateServerSocketCreation()
{
  if (this->fd < 0)
  {
    perror("failed to create a server socket!");
    exit(1);
  }
  std::cout << "server socket created!" << std::endl;
}

void Server::configServerNonBlocking()
{
  int flag = fcntl(this->fd, F_GETFL, 0);

  if (flag == -1)
  {
    perror("error: fcntl(F_GETFL)");
    close(this->fd);
    exit(1);
  }

  if (fcntl(this->fd, F_SETFL, flag | O_NONBLOCK) == -1)
  {
    perror("error: fcntl(F_SETFL)");
    close(this->fd);
    exit(1);
  }
}

void Server::configServerReuseAddress()
{
  int opt = 0;

  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
  {
    std::cerr << "setsockopt err\n" << std::endl;
    close(this->fd);
    exit(1);
  }
}
