#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <list> 
#include <string>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_LEN 200
#define NUM_COLORS 6
using namespace std;

class Server
{
    struct terminal
    {
    int id;
    string name;
    SOCKET socket;
    thread th;
    };

 //   vector<terminal> clients;
    list<terminal> clients; // Use std::list instead of std::vector

    string def_col = "\033[0m";
    string colors[NUM_COLORS] = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m" };
    int seed = 0;
    mutex cout_mtx, clients_mtx;

    // Private helper methods
    string color(int code);
    void set_name(int id, char name[]);
    void shared_print(const std::string& str, bool endLine = true);
    int broadcast_message(const std::string& message, int sender_id);
    int broadcast_message(int num, int sender_id);
    void end_connection(int id);
    void handle_client(SOCKET client_socket, int id);


public:
    Server(); // Constructor to handle initialization tasks.
    ~Server(); // Destructor to handle cleanup tasks.
    void start(); // Main loop for the server to handle incoming connections.

};

#endif // SERVER_H
