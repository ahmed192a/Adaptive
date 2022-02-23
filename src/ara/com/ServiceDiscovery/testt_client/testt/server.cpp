#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "Service_Discovery/server/CServer.h"
#include "skeleton.h"

using namespace std;


struct C_Info
{
    int process_id;
    char method_name[30];
    int param1;
    int param2;
};


int main(int argc, char **argv)
{
    int portNum = atoi(argv[1]);

    skeleton s1(portNum, atoi(argv[2]), 32);
    // send to service discovery the offered service
    s1.start_service();

    /* TCP */
    char buffer[256];
    CServer s2(SOCK_STREAM);
    s2.OpenSocket(portNum);
    s2.BindServer();
    s2.ListenServer(1); 
    s2.AcceptServer();
    cout<<"accepted\n";

    strcpy(buffer, "=> Server connected...\n");
    // send a confirmation connect to client
    s2.SendServer(buffer, strlen(buffer));

    struct  C_Info x;
    
    // Receive a struct from client containing the method name and parameters
    s2.ReceiveServer((struct C_Info*) &x, sizeof(struct C_Info));

    // print the requested method
    cout<<x.method_name<<endl;

    // Perform the requested method then send the result
    s1.method_dispatch(x, s2);


    cout << "\nGoodbye..." << endl;

    s1.StopOfferService();
    
    s2.CloseSocket();
}