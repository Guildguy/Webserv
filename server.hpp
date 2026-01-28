#ifndef  SERVER_HPP
#define  SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class  Server
{
  private:
    int          fd;
    sockaddr_in  saddr;

    bool configServerNonBlocking();
    bool configServerReuseAddress();
    bool validateServerSocketCreation();


  public:
    bool createAndConfigServersocket();
  
};

#endif
