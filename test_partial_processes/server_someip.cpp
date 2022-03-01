#include "../src/ara/com/ipc/server/socket_Server.h"


#include <iostream>
using namespace std;
int main()
{
    
    cout<<"server"<<endl;
    CServer servertest(SOCK_DGRAM);
    servertest.OpenSocket(2025);
    servertest.BindServer();
    struct sockaddr_in sd;
    sd.sin_family = AF_INET; // IPv4
    sd.sin_addr.s_addr = INADDR_ANY;
    sd.sin_port = htons(2033);
    char buffer [] = "some ip message";
    //sd.sa_data;

    servertest.UDPSendTo(&buffer, sizeof(buffer), (const sockaddr *)&sd);
    int x;
    cin>>x;
    return 0;
}



