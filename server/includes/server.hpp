#ifndef  SERVER_HPP
#define  SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class  Server
{
    private:
        int                 fd;
        struct sockaddr_in  saddr;

        bool  configServerNonBlocking();
        bool  configServerReuseAddress();
        bool  ConfigServerAddress(int Port, const std::string& IP);
        bool  bindServerSocket();
        bool  socketListener();
        
        bool  handleError(const std::string& msg);
        bool  validateServerSocketCreation();
        void  closeServerFD();

    public:
        Server();
        ~Server();

        bool  createAndPreConfigServerSocket();
        bool  initializeServer(int Port, const std::string &IP);
    
};

#endif

//ncdu