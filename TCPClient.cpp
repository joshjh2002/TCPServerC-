// include C++ IO and windows socket library

#include <iostream>
#include <winsock2.h>

// declared namespaces for print

using namespace std;
class TCPClient
{
private:
    WSADATA WSAData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddress;

public:
    TCPClient(char *ip, int port)
    {
        WSAStartup(MAKEWORD(2, 0), &WSAData); // WSAStartup function initiates use of the Winsock DLL by a process, it is version 2

        serverSocket = socket(AF_INET, SOCK_STREAM, 0); // This establishes a socket and connection oriented, SOCK_STREAM that is for TCP

        serverAddress.sin_addr.s_addr = inet_addr(ip); // it is a loopback ip as server and client are running in the same machine
        serverAddress.sin_family = AF_INET;            // AF_INET is an address family in internet domain that is used to designate IPv4 that your socket can communicate
        serverAddress.sin_port = htons(port);          // Port is declared
    }

    void connectToServer()
    {
        connect(serverSocket, (SOCKADDR *)&serverAddress, sizeof(serverAddress)); // connect server socket
        cout << "Connected to server!\n";                     // printing the message
    }

    void sendMessage()
    {
        char buffer[4096] = "This is my TCP Server";
        send(serverSocket, buffer, sizeof(buffer), 0);
        cout << "Message sent!\n";
    }

    void terminateConnection()
    {
        closesocket(serverSocket);
        WSACleanup();
        cout << "Socket closed.\n";
    }
};

//declare main methods
int main()
{
    TCPClient *myClient = new TCPClient("127.0.0.1", 6666);

    myClient->connectToServer();
    myClient->sendMessage();
    myClient->terminateConnection();
}
