#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "fileDescriptor.hpp"

class   ClientSocket
{
    private:
        private:
            FileDescriptor _fd;

        public:
            ClientSocket();
            explicit ClientSocket(int fd);
            ~ClientSocket();
}

#endif