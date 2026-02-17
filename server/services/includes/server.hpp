#ifndef  SERVER_HPP
#define  SERVER_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <cstddef>
#include <sys/socket.h>
#include "../../domain/includes/port.hpp"
#include "../../domain/includes/ipAddr.hpp"
#include "../../infra/includes/fileDescriptor.hpp"
#include "../../infra/includes/serverSocket.hpp"
#include "../../infra/includes/clientSocket.hpp"
#include "connectionManager.hpp"
#include "pollManager.hpp"
#include "epollManager.hpp"

enum EventType
{
	POLL,
	EPOLL
};

class  Server
{
    private:
        ServerSocket			_serverSocket;
        EventManager*			_eventManager;
        ConnectionManager*		_connectionManager;
        bool					_isValid;
        
        bool	handleError(const std::string& msg);

    public:
        Server();
        Server(EventType type, const Port& port, const IpAddr& ipAddr);
        ~Server();

        bool	isValid() const;
        void	run();
};

#endif

//ncdu