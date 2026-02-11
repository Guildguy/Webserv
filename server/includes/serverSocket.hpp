#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "fileDescriptor.hpp"

class   ServerSocket
{
    private:
        FileDescriptor  _fd;
        sockaddr_in     _saddr;

        bool    createSocket();

    public:
        ServerSocket();
        ~ServerSocket();

        bool    initialize(int port, const str::string& ipAddr);
};

#endif
