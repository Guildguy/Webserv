#include "includes/server.hpp"

bool    Server::handleError(const std::string& msg)
{
    perror(msg.c_str());
    return (false);
}

bool    Server::closeServerFD()
{
    _server_fd.invalidate();
    return (false);
}
