#include "Client.h"

int main() {
    Client myClient;
    try {
        myClient.connect_to_server("127.0.0.1", 10000);
        myClient.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
