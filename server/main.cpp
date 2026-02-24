#include "services/includes/server.hpp"

int main()
{
    try
    {
        std::cout << "Initializing server on port 8080..." << std::endl;
        
        Port port(8080);
        IpAddr ipAddr("0.0.0.0");
        Server server(POLL, port, ipAddr);
        
        if (!server.isValid())
        {
            std::cerr << "Failed to initialize server!" << std::endl;
            return (1);
        }

        std::cout << "Server started successfully!" << std::endl;
        std::cout << "Listening on: " << ipAddr.getValue() << ":" << port.getValue() << std::endl;
        std::cout << "Test with: telnet localhost " << port.getValue() << std::endl;
        
        server.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return (1);
    }
    
    return (0);
}
