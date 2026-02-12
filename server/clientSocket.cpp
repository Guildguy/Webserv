#include "includes/clientSocket.hpp"

ClientSocket::ClientSocket() : _fd(-1) {}

ClientSocket::ClientSocket(int fd) : _fd(fd) {}

clientSocket::~ClientSocket() {}