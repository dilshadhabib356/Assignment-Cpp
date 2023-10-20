#include "Client.h"
#include <iostream>

using namespace std;


// Constructor: Initializes the client by setting up a socket and winsock.
Client::Client() {
    try {
        WSADATA wsaData;

        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);                 // Start winsock
        if (iResult != 0) {
            throw std::runtime_error("WSAStartup failed");
        }

        client_socket = socket(AF_INET, SOCK_STREAM, 0);                            // Create the client's socket
        if (client_socket == INVALID_SOCKET) {
            WSACleanup();
            throw std::runtime_error("Socket creation failed");
        }
    }
    catch (const std::exception& e) {
        cerr << "Error in Client constructor: " << e.what() << endl;
        exit(-1);
    }
}

// Destructor
Client::~Client() {
    stop();
}


// A utility to pick a color for the client
string Client::color(int code) {
    return colors[code % NUM_COLORS];
}

int Client::eraseText(int cnt)          // function to erase some characters from the console.
{
    char back_space = 8;
    for (int i = 0; i < cnt; i++) {
        cout << back_space;
    }
    return cnt;
}

void Client::send_message()         // Threaded function -- client sending messages.

{
    while (!exit_flag) {
        cout << colors[1] << "You : " << def_col;
        char str[MAX_LEN];
        cin.getline(str, MAX_LEN);
        send(client_socket, str, sizeof(str), 0);
        if (strcmp(str, "#exit") == 0)                  // If the user types #exit, break from the loop.
        
        {
            exit_flag = true;
            return;
        }
    }
}

void Client::recv_message()             //client receiving messages.
{
    while (!exit_flag) {
        char name[MAX_LEN], str[MAX_LEN];
        int color_code;
        int bytes_received = recv(client_socket, name, sizeof(name), 0);
        if (bytes_received <= 0)
            continue;
        recv(client_socket, (char*)&color_code, sizeof(color_code), 0);
        recv(client_socket, str, sizeof(str), 0);
        eraseText(6);
        if (strcmp(name, "#NULL") != 0)                 // Check if the message is from a user or a system message.
            cout << color(color_code) << name << " : " << def_col << str << endl;
        else
            cout << color(color_code) << str << endl;
        cout << colors[1] << "You : " << def_col;
        fflush(stdout);
    }
}

void Client::connect_to_server(const std::string& serverIP, int port)           //connet server and initialize the sending and receiving threads. 

{
    try {
        sockaddr_in client;
        client.sin_family = AF_INET;
        client.sin_port = htons(port);
        inet_pton(AF_INET, serverIP.c_str(), &(client.sin_addr));

        if (connect(client_socket, (struct sockaddr*)&client, sizeof(client)) == SOCKET_ERROR)         // Try to connect to the server.
        {
            throw std::runtime_error("Connection to server failed");
        }

        char name[MAX_LEN];
        cout << "Enter your name : ";
        cin.getline(name, MAX_LEN);
        send(client_socket, name, sizeof(name), 0);

        cout << colors[NUM_COLORS - 1] << "\n\t  ====== Welcome to the chat-room Application ======   " << endl << def_col;

        t_send = thread(&Client::send_message, this);
        t_recv = thread(&Client::recv_message, this);
    }
    catch (const std::exception& e) {
        cerr << "Error in connect_to_server: " << e.what() << endl;
        stop();
        exit(-1);
    }
}



void Client::run() // Main loop where the client runs
{
    try {
        if (t_send.joinable()) {
            t_send.join();
        }
        if (t_recv.joinable()) {
            t_recv.join();
        }
    }
    catch (const std::exception& e) {
        cerr << "Error in run: " << e.what() << endl;
    }
}




void Client::stop()                 // Cleanup function to properly close the client's connection and threads.
{
    try {
        if (t_send.joinable()) {
            t_send.detach();
        }
        if (t_recv.joinable()) {
            t_recv.detach();
        }
        closesocket(client_socket);
        WSACleanup();
    }
    catch (const std::exception& e) 
    {
        cerr << "Error in stop: " << e.what() << endl;
    }
}