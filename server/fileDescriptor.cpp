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
