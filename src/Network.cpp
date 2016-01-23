#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512
#define _WIN32_WINNT  0x501

#include <windows.h>
#include <ws2tcpip.h>
#include <winsock2.h>
#include "Network.h"

Network::Network()
{
    isError_=false;
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        std::cout<<std::endl<<"WSAStartup failed:"<<iResult<<std::endl;
        return;
    }
}

Network::~Network()
{
    //dtor
}

void Network::StartClient(std::string ip)
{
    int iResult;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(ip.c_str(), DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        //printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        isError_=true;
        error_="getaddrinfo failed";
        std::cout<<std::endl<<"getaddroinfo failed:"<<iResult<<std::endl;
        return;
    }

    ConnectSocket_ = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo

    ptr=result;

    // Create a SOCKET for connecting to server
    ConnectSocket_ = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket_ == INVALID_SOCKET)
    {
        //printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        isError_=true;
        error_="Error at socket()";
        return;
    }

    // Connect to server.
    iResult = connect( ConnectSocket_, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket_);
        ConnectSocket_ = INVALID_SOCKET;
        isError_=true;
        error_="SOCKET_ERROR";
        return;
    }

    freeaddrinfo(result);

    if (ConnectSocket_ == INVALID_SOCKET)
    {
        //printf("Unable to connect to server!\n");
        WSACleanup();
        isError_=true;
        error_="Unable to connect to server";
        return;
    }
}

void Network::StartServer()
{
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        //printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        //printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        //printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        //printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // Accept a client socket
    /*ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        //printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }*/

    return;
}


void Network::CloseClientConnection()
{
    if(ConnectSocket_!=INVALID_SOCKET)
    {
        closesocket(ConnectSocket_);
        WSACleanup();
    }
}

void Network::CloseServer()
{

}

bool Network::isError()
{
    return isError_;
}

std::string Network::getLastError()
{
    return error_;
}
