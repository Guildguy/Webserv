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
    int flag = fcntl(fd, F_GETFL, 0);
    if (flag == -1)
        return (false);
    if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1)
        return (false);
    return (true);
}

bool FileDescriptor::setReuseAddress()
{
    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        return (false);
    return (true);
}

bool FileDescriptor::operator==(const FileDescriptor& other) const
{
    return (_fd == other._fd);
}

bool FileDescriptor::operator<(const FileDescriptor& other) const
{
    return (_fd < other._fd);
}
