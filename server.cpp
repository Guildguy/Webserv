#include "server.hpp"

int  create_n_config_socket()
{
  Server.fd = socket(AF_NET, SOCK_STREAM, 0);
  //ERR TREATMENT
  if (Server.fd < 0)
  {
    std::cout << "failed to create a server socket!" << std::endl;
    close(Server.fd);
    exit(1);
  }
  str::cout << "Server socket created!" << std::endl;

  //SEPARAR POSTERIORMENTE
  int flag = fcntl(Server.fd, F_GETFL, 0);
  if (flag == -1)
  {
    perror("error: fcntl(F_GETFL)");
    close(Server.fd);
    exit(1);
  }

  fcntl(Server.fd, F_SETFL, flag | O_NONBLOCK) == -1
  {
    perror("error: fcntl(F_SETFL)");
    close(Server.fd);
    exit(1);
  }
}
