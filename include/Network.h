#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <iostream>

class Network
{
    public:
        Network();
        virtual ~Network();
        bool isServerUp();
        void StartClient(std::string ip);
        void StartServer();
        void CloseClientConnection();
        void CloseServer();
        bool isError();
        std::string getLastError();
    protected:

    private:
        SOCKET ConnectSocket_;
        SOCKET ListenSocket_;
        bool isError_;
        std::string error_;
};

#endif // NETWORK_H
