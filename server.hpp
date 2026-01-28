#ifndef  SERVER_HPP
#define  SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

class  Server
{
  private:

  public:
    sockaddr_in  saddr;
    int          fd;
  
};

#endif
