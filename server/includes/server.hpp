#ifndef  SERVER_HPP
#define  SERVER_HPP

#include "fileDescriptor.hpp"
#include "serverSocket.hpp"
#include "clientSocket.hpp"

class  Server
{
    private:
        ServerSocket                    _serverSocket;
        std::vector<pollfd>             _pollFds;
        
		void	acceptNewClient();
		void   	handleClientData(size_t index);

        bool	handleError(const std::string& msg);

    public:
        Server();
        ~Server();

        bool	initialize(int Port, const std::string &IP);
		void	run();
    
};

#endif

//ncdu