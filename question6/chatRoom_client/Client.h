#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_LEN 200        // Defne max length for messages.
#define NUM_COLORS 6       // Number of avilable colors.

class Client
{
private:
    SOCKET client_socket;               // Socket for connect with server.
    std::string def_col = "\033[0m";    // Defualt clr.
    std::string colors[NUM_COLORS] = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m" };  // Color codes for display.

    std::thread t_send, t_recv;         // Threads for send & recv messages.
    bool exit_flag = false;             // Flag to see client exit state.

    std::string color(int code);        // Return colour based on client ID.
    int eraseText(int cnt);             // Erase specific number of char in console.
    void send_message();                // Handling send msgs to server.
    void recv_message();                // Handling recv msgs from server.

public:
    Client();                           // Constructor, init client, set up resources.
    ~Client();                          // Destructor, cleanup and stops if still running.
    void connect_to_server(const std::string& serverIP, int port);  // Connect client to server with IP & port.
    void run();                         // Main client operation loop.
    void stop();                        // Stop & disconnect client, free up resources.
};

#endif // CLIENT_H
