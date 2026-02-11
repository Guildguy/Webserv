#include "includes/server.hpp"

bool    Server::handleError(const std::string& msg)
{
    perror(msg.c_str());
    return (false);
}

bool    Server::closeServerFD()
{
    if (this->fd != -1)
    {
        close(this->fd);
        this->fd = -1;
    }
    return (false);
}
