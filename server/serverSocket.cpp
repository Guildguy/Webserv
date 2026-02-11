#include "includes/serverSocket.hpp"

ServerSocket::ServerSocket() {}

ServerSocket::~ServerSocket() {}

bool    ServerSocket::initialize(int port, const str:string& ipAddr)
{
    if (!createSocket())
        return (false);
    if (!configAddr(port, IpAddr))
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

bool    ServerSocket::configAddr(int port, const std::string& IpAddr)
{
    _saddr.sin_family = AF_INET;
    _saddr.sin_port = htons(Port);
    
    if (IP == "0.0.0.0" || IP.empty())
    {
        _saddr.sin_addr.s_addr = INADDR_ANY;
        return (true);
    }
    
    in_addr_t addr = inet_addr(IP.c_str());
    if (addr == INADDR_NONE)
        return (handleError("error: invalid IP address"));
    
    _saddr.sin_addr.s_addr = addr;
    return (true);
}