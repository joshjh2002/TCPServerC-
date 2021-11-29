// annotate all what is what

#include <iostream>
#include <winsock2.h>

using namespace std;

class TCPServer
{
    WSADATA WSAData;

    SOCKET serverSocket, clientSocket;

    SOCKADDR_IN serverAddress, clientAddress;

public:
    //Initialise Server
    TCPServer(int port)
    {
        WSAStartup(MAKEWORD(2, 0), &WSAData);

        // add code here for TCP serversocket

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        serverAddress.sin_addr.s_addr = INADDR_ANY;

        // add code here for ip family

        serverAddress.sin_family = AF_INET;

        serverAddress.sin_port = htons(port);

        bind(serverSocket, (SOCKADDR *)&serverAddress, sizeof(serverAddress));
        listen(serverSocket, 0);

        cout << "Listening for incoming connections..." << endl;
    };

    void receiveMessage()
    {
        char buffer[4096];
        int clientAddrSize = sizeof(clientAddress);
        if ((clientSocket = accept(serverSocket, (SOCKADDR *)&clientAddress, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Client connected!" << endl;
            recv(clientSocket, buffer, sizeof(buffer), 0);
            cout << "Client says: " << buffer << endl;
            memset(buffer, 0, sizeof(buffer));
        }
    }

    void terminateConnection()
    {
        closesocket(clientSocket);
        WSACleanup();
        cout << "Client disconnected." << endl;
    }
};

int main()
{
    TCPServer *myServer = new TCPServer(6666);
    myServer->receiveMessage();
    myServer->terminateConnection();
}
