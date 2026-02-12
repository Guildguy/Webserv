#include "includes/clientSocket.hpp"

ClientSocket::ClientSocket() : _fd(-1) {}

ClientSocket::ClientSocket(int fd) : _fd(fd)
{
    if (_fd.isValid())
        _fd.setNonBlocking();
}

clientSocket::~ClientSocket()
{
    invalidate();
}

void    ClientSocket::invalidate()
{
    _fd.invalidate();
}

bool    ClientSocket::isValid() const 
{
    return (_fd.isValid());
}
