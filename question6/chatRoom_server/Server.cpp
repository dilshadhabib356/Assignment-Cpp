#include "Server.h"

Server::Server() {
    try {
        WSADATA wsaData;                                  // Initialize WinSock data.
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            throw std::runtime_error("WSAStartup failed with error: " + std::to_string(iResult));
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;                        // Output the error.
        exit(-1);                                        // Terminate the application.
    }
}

Server::~Server() {
    for (terminal& client : clients) {                   // Iterate through all clients.
        if (client.th.joinable()) client.th.join();      // Ensure threads are safely joined.
    }
    WSACleanup();                                        // Cleanup WinSock.
}

string Server::color(int code) { return colors[code % NUM_COLORS]; } // Fetch a color based on the code.

void Server::set_name(int id, char name[]) {
    for (auto& client : clients) {                       // Iterate through all clients.
        if (client.id == id) {
            client.name = string(name);                  // Set name for matched client.
        }
    }
}

void Server::shared_print(const string& str, bool endLine) {
    lock_guard<mutex> guard(cout_mtx);                   // Lock to ensure thread safety.
    cout << str;
    if (endLine) cout << endl;                           // Decide to end the line based on flag.
}

int Server::broadcast_message(const string& message, int sender_id) {
    char temp[MAX_LEN];
    strcpy_s(temp, sizeof(temp), message.c_str());
    for (auto& client : clients) {                       // Iterate through all clients.
        if (client.id != sender_id) {                    // Don't send to the sender itself.
            send(client.socket, temp, sizeof(temp), 0);
        }
    }
    return 0;
}

int Server::broadcast_message(int num, int sender_id) {
    for (auto& client : clients) {                       // Iterate through all clients.
        if (client.id != sender_id) {                    // Don't send to the sender itself.
            send(client.socket, (const char*)&num, sizeof(num), 0);
        }
    }
    return 0;
}

void Server::end_connection(int id) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if (it->id == id) {
            lock_guard<mutex> guard(clients_mtx);         // Lock to ensure thread safety.
            it->th.detach();                              // Detach the thread.
            closesocket(it->socket);                      // Close the associated socket.
            clients.erase(it);                            // Remove the client from list.
            break;
        }
    }
}

void Server::handle_client(SOCKET client_socket, int id) {
    try {
        char name[MAX_LEN], str[MAX_LEN];
        recv(client_socket, name, sizeof(name), 0);
        set_name(id, name);                               // Set the client's name.

        string welcome_message = string(name) + " has joined";
        broadcast_message("#NULL", id);                   // Send initial messages.
        broadcast_message(id, id);
        broadcast_message(welcome_message, id);
        shared_print(color(id) + welcome_message + def_col);

        while (true) {
            int bytes_received = recv(client_socket, str, sizeof(str), 0);
            if (bytes_received <= 0) break;               // If no bytes received or error, exit.

            if (strcmp(str, "#exit") == 0) {
                string message = string(name) + " has left";
                broadcast_message("#NULL", id);
                broadcast_message(id, id);
                broadcast_message(message, id);
                shared_print(color(id) + message + def_col);
                end_connection(id);                        // End the client connection.
                break;
            }

            broadcast_message(string(name), id);          // Broadcast the received message.
            broadcast_message(id, id);
            broadcast_message(string(str), id);
            shared_print(color(id) + name + " : " + def_col + str);
        }
    }
    catch (const std::exception& e) {
        cerr << "Error in handle_client: " << e.what() << endl; // Handle and print errors.
    }
}


void Server::start() {
    try {
        WSADATA wsaData;                                  // Initialize WinSock data.
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            throw std::runtime_error("WSAStartup failed with error: " + std::to_string(iResult));
        }

        SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);   // Create server socket.
        if (server_socket == INVALID_SOCKET) {
            throw std::runtime_error("Socket failed with error: " + std::to_string(WSAGetLastError()));
        }

        sockaddr_in server;                               // Structure to hold server information.
        server.sin_family = AF_INET;
        server.sin_port = htons(10000);                   // Port number: 10000.
        server.sin_addr.S_un.S_addr = INADDR_ANY;         // Accept connections on all network interfaces.
        ZeroMemory(&(server.sin_zero), 8);                // Clear out sin_zero for compatibility.

        if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {   // Bind the socket.
            throw std::runtime_error("Bind failed with error: " + std::to_string(WSAGetLastError()));
        }

        if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {  // Start listening for incoming connections.
            throw std::runtime_error("Listen failed with error: " + std::to_string(WSAGetLastError()));
        }

        shared_print("Server started. Awaiting connections...");  // Notify that the server has started.

        sockaddr_in client;                               // Structure to hold client information.
        int client_size = sizeof(client);

        while (true) {                                    // Infinite loop to keep accepting new connections.
            SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client, &client_size);  // Accept new client connection.
            if (client_socket == INVALID_SOCKET) {
                throw std::runtime_error("Accept failed with error: " + std::to_string(WSAGetLastError()));
            }
            seed++;                                      // Increase the seed for unique client ID.
            thread t(&Server::handle_client, this, client_socket, seed);  // Spawn a new thread to handle the client.
            lock_guard<mutex> guard(clients_mtx);         // Acquire lock before modifying the clients list.
            clients.push_back({ seed, "Anonymous", client_socket, move(t) });  // Add new client to clients list.
        }

        for (terminal& client : clients) {                // Go through each client.
            if (client.th.joinable()) client.th.join();   // Join any active threads.
        }

        closesocket(server_socket);                       // Close the server socket.
        WSACleanup();                                     // Cleanup WinSock.
    }
    catch (const std::exception& e) {                     // Catch any thrown exceptions.
        cerr << "Error in start: " << e.what() << endl;   // Print error message.
    }
}
