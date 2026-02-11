#ifndef FILE_DESCRIPTOR_HPP
#define FILE_DESCRIPTOR_HPP

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
        bool    setReuseAddress();

        int     get() const;

        bool    operator==(const FileDescriptor& other) const;
        bool    operator<(const FileDescriptor& other) const;
};

#endif
