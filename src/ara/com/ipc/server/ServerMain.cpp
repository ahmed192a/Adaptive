

#include <iostream>
#include "CServer.h"
#include <string>
#include <cstring>
using namespace std;
int main(int argc, char *argv[])
{
    //std::string m;
    char buffer[256];
    CServer s1(SOCK_STREAM);
    s1.OpenSocket(2020);
    s1.BindServer();
    s1.ListenServer(5); 
    s1.AcceptServer();
    cout<<"accepted\n";
    s1.ReceiveServer(buffer);
    cout<<buffer<<endl;
    //m = "hello c";
    strcpy(buffer, "hello c");
    s1.SendServer(buffer);
    s1.CloseSocket();
    cout<<"Finish\n";

    
    return  0;
}