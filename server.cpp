#include "server.hpp"

int  create_n_config_socket(Server &server)
{
  server.fd = socket(AF_INET, SOCK_STREAM, 0);
  //ERR TREATMENT
  if (server.fd < 0)
  {
    perror("failed to create a server socket!");
    close(server.fd);
    exit(1);
  }
  std::cout << "server socket created!" << std::endl;

  //SEPARAR POSTERIORMENTE
  int flag = fcntl(server.fd, F_GETFL, 0);
  if (flag == -1)
  {
    perror("error: fcntl(F_GETFL)");
    close(server.fd);
    exit(1);
  }

  if (fcntl(server.fd, F_SETFL, flag | O_NONBLOCK) == -1)
  {
    perror("error: fcntl(F_SETFL)");
    close(server.fd);
    exit(1);
  }

  //SEPARAR POSTERIORMENTE
  int opt = 0;

  if (setsockopt(server.fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
  {
    std::cerr << "setsockopt err\n" << std::endl;
    close(server.fd);
    exit(1);
  }
}
