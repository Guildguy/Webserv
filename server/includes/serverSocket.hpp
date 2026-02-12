#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "fileDescriptor.hpp"

class   ServerSocket
{
    private:
        FileDescriptor  _fd;
        sockaddr_in     _saddr;

        bool    createSocket();
        bool    configAddr(int port, const std::string& IpAddr);

    public:
        ServerSocket();
        ~ServerSocket();

        bool    initialize(int port, const str::string& ipAddr);
        bool    setBind();
        bool    setListen(int backlog);
        int     setAccept();

        int     getPollFd() const;
        bool    isValid() const;
        
};

#endif
