// We are not using this file anymore, we're using the service_proxy
#include "proxy.hpp"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "../ipc/client/socket_Client.h"
#include "../ipc/server/socket_Server.h"

#include "data.h"

using namespace std;

struct C_Info
{
    int process_id;
    char method_name[30];
    int param1;
    int param2;
};

int proxy::Create(int portNumber, int service_id)
{
    // Send a srevice id to the service discovery
    // receive the port number of the server that provides this service
    char buffer[256];
    char hostbuffer[256];
    CClient c1(SOCK_STREAM);
    c1.OpenSocket();
    bzero(hostbuffer,256);
	int hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

	if(hostnameRet < 0)
	{
		cout<<("Unable to local machine get Host Name\n");
	}

    c1.GetHost("127.0.0.1", portNumber);
    c1.ClientConnect();

    // send the service id
    c1.ClientWrite(&service_id, sizeof(int));

    // receive the port number
    c1.ClientRead(&this->server_port_number, sizeof(int));
    cout << "Received port number: " << this->server_port_number << endl;
    cout << "\n=> Connection terminated.\nGoodbye...\n";

    c1.CloseSocket();

    return 0;
}

int proxy::Method()
{    
    int bufsize = 1024;
    char buffer[bufsize];
    char hostbuffer[256];
    CClient c1(SOCK_STREAM);
    c1.OpenSocket();
    bzero(hostbuffer,256);
	int hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

	if(hostnameRet < 0)
	{
		cout<<("Unable to local machine get Host Name\n");
	}

    // talk to the server using the received port number
    c1.GetHost("127.0.0.1", this->server_port_number);
    c1.ClientConnect();

    // Receive a confirmation message from the server
    cout << "=> Awaiting confirmation from the server2..." << endl; //line 40
    bzero(buffer, bufsize);
    c1.ClientRead(buffer, 256);
    cout << buffer<<endl;
    cout << "=> Connection confirmed, you are good to go...";

    struct C_Info x = {getpid(), "add", 3, 2};

    // send the requested method, and the parameters
    c1.ClientWrite(&x, sizeof(struct C_Info));

    cout << "The method is sent to the server" << endl;

    int result; // to save the result of the method

    // receive the methods result
    c1.ClientRead((int*)&result, sizeof(int));
    cout << "Received result: " << result << endl;
    cout << "\n=> Connection terminated.\nGoodbye...\n";

    c1.CloseSocket();

    return 0;
}

proxy::proxy(/* args */)
{

}
proxy::~proxy()
{

}