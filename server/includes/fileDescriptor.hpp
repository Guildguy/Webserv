#ifndef FILE_DESCRIPTOR_HPP
#define FILE_DESCRIPTOR_HPP

#include "server.hpp"

class FileDescriptor
{
    private:
        int _fd;

    public:
        explicit FileDescriptor();
        FileDescriptor(int fd);

        bool    isValid() const;
        int     getValue() const;
        void    invalidate();

        bool    operator==(const FileDescriptor& other) const;
        bool    operator<(const FileDescriptor& other) const;
};

#endif