#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "fileDescriptor.hpp"
#include "../../domain/includes/port.hpp"
#include "../../domain/includes/ipAddr.hpp"

class   ServerSocket
{
    private:
        FileDescriptor  _fd;
        sockaddr_in     _saddr;

        void    configAddr(const Port& port, const IpAddr& ipAddr);

    public:
        ServerSocket();
        ServerSocket(const Port& port, const IpAddr& ipAddr);
        ~ServerSocket();
        bool    setBind();
        bool    setListen(int backlog);
        int     setAccept();

        int     getPollFd() const;
        bool    isValid() const;
        
};

#endif
