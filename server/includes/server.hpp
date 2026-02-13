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
        std::vector<ClientSocket*>      _clients;
        bool                            _isValid;
        
		void	acceptNewClient();
		void   	handleClientData(size_t index);

        bool	handleError(const std::string& msg);

    public:
        Server();
        Server(int Port, const std::string &IpAddr);
        ~Server();

        bool    isValid() const;
		void	run();
    
};

#endif

//ncdu