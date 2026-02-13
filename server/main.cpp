#include "includes/server.hpp"

int main()
{
    std::cout << "Initializing server on port 8080..." << std::endl;
    
    Server server(8080, "0.0.0.0");
    
    if (!server.isValid())
    {
        std::cerr << "Failed to initialize server!" << std::endl;
        return 1;
    }

    std::cout << "Server started successfully!" << std::endl;
    std::cout << "Listening on 0.0.0.0:8080" << std::endl;
    std::cout << "Test with: telnet localhost 8080" << std::endl;
    
    server.run();
    
    return 0;
}
