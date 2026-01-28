#include "server.hpp"

int  create_n_config_socket()
{
  Server.fd = socket(AF_NET, SOCK_STREAM, 0);
  //ERR TREATMENT
  if (Server.fd < 0)
  {
    perror("failed to create a server socket!");
    close(Server);
    exit(1);
  }
  str::cout << "Server socket created!" << std::endl;

  //SEPARAR POSTERIORMENTE
  int flag = fcntl(Server.fd, F_GETFL, 0);
  if (flag == -1)
  {
    perror("error: fcntl(F_GETFL)");
    close(Server);
    exit(1);
  }

  fcntl(Server.fd, F_SETFL, flag | O_NONBLOCK) == -1
  {
    perror("error: fcntl(F_SETFL)");
    close(Server);
    exit(1);
  }

  int opt = 0;

  if (setsockopt(Server.fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
  {
    std::cerr << "setsockopt err\n" << std::endl;
    close(Server);
    exit(1;)
  }
}
