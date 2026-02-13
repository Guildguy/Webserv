#ifndef FILE_DESCRIPTOR_HPP
#define FILE_DESCRIPTOR_HPP

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <cstdlib>
#include <cerrno>
#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include <arpa/inet.h>

class FileDescriptor
{
    private:
        int _fd;

        FileDescriptor(const FileDescriptor&);
        FileDescriptor& operator=(const FileDescriptor&);

    public:
        FileDescriptor();
        explicit FileDescriptor(int fd);
		~FileDescriptor();

        bool    isValid() const;
        void    invalidate();

        bool    setNonBlocking();

        int     get() const;

        bool    operator==(const FileDescriptor& other) const;
        bool    operator<(const FileDescriptor& other) const;
        
};

#endif
