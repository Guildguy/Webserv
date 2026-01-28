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

    bool  handleError(const std::string& msg);
    bool configServerNonBlocking();
    bool configServerReuseAddress();
    bool validateServerSocketCreation();
    void closeServerFD();


  public:
    Server();
    ~Server();

    bool createAndConfigServersocket();
  
};

#endif
