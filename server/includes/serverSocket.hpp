#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "fileDescriptor.hpp"

class   ServerSocket
{
    private:
        FileDescriptor  _fd;
        sockaddr_in     _saddr;

        void    configAddr(int port, const std::string& ipAddr);

    public:
        ServerSocket();
        ServerSocket(int port, const std::string& ipAddr);
        ~ServerSocket();
        bool    setBind();
        bool    setListen(int backlog);
        int     setAccept();

        int     getPollFd() const;
        bool    isValid() const;
        
};

#endif
