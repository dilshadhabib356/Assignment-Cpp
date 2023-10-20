#include "Server.h"

int main() {
    Server myServer;  // Instantiate the server

    try {
        myServer.start();  // Start the server
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
        return 2;
    }
    
    return 0;
}
