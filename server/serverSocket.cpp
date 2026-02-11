#include "includes/serverSocket.hpp"

ServerSocket::ServerSocket() {}

ServerSocket::~ServerSocket() {}

bool    ServerSocket::initialize(int port, const str:string& ipAddr)
{
    if (!createSocket())
        return (false);
    return (true);
}

bool    ServerSocket::createSocket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    _fd = FileDescriptor(fd);

    if (!_fd.isValid())
        return (handleError("error: socket creation failed"));
    if (!_fd.setNonBlocking())
        return (handleError("error: setNonBlocking failed"));
    
    int opt = 1;
    if (setsockopt(_fd.get(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        return (handleError("error: setsockopt failed"));

    return (true);
}