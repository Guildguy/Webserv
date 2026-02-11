#include "includes/fileDescriptor.hpp"

FileDescriptor::FileDescriptor() : _fd(-1) {}

FileDescriptor::FileDescriptor(int fd) : _fd(fd) {}

FileDescriptor::~FileDescriptor()
{
    invalidate();
}

bool FileDescriptor::isValid() const
{
    return (_fd >= 0);
}

int FileDescriptor::getValue() const
{
    return (_fd);
}

void FileDescriptor::invalidate()
{
    if (_fd != -1)
    {
        close(_fd);
        _fd = -1;
    }
}

bool FileDescriptor::setNonBlocking()
{
    return (FileDescriptor::setNonBlocking(_fd));
}

bool FileDescriptor::setReuseAddress()
{
    return (FileDescriptor::setReuseAddress(_fd));
}

bool FileDescriptor::setNonBlocking(int fd)
{
    int flag = fcntl(fd, F_GETFL, 0);
    if (flag == -1)
        return (false);
    if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1)
        return (false);
    return (true);
}

bool FileDescriptor::setReuseAddress(int fd)
{
    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        return (false);
    return (true);
}
