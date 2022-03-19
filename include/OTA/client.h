#ifndef CLIENT_H
#define CLIENT_H

#include <iostream> //cout
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>// close socket

#define IP_CLOUD "127.0.0.1"
#define PORT_CLOUD 8888
#define BUFFER_SIZE 100000

using namespace std;

class Client
{
private:
        int sock;
        struct sockaddr_in server;
        string address;
        int port;

        bool sendData(string data);


    public:
        Client();
        
        bool cloudConnect(string address, int port);
        bool requestMetadata(char * data);
        bool requestPackage(char * data);
        void cloudDisconnect();
};

#endif