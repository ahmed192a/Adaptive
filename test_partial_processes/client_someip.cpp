#include "../src/ara/com/ipc/server/socket_Server.h"
#include "../src/ara/com/ipc/client/socket_Client.h"

#include <iostream>
using namespace std;
int main()
{
    CServer clienttest(SOCK_DGRAM);
    clienttest.OpenSocket(2033);
    clienttest.BindServer();
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer [16];
    clienttest.UDPRecFrom(&buffer, sizeof(buffer), (struct sockaddr *) &cliaddr, &len);
    buffer[15]='\0';
    
    printf("%s\n", buffer);
    int x;
    cin>>x;

    //sd.sa_data;

    return 0;
}