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

int     ClientSocket::getPollFd() const
{
    return (_fd.getPollFd);
}

ssize_t ClientSocket::receiveData(char* buffer, size_t size)
{

}

ssize_t ClientSocket::sendData(const char* data, size_t size)
{
    
}