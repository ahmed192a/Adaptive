#include <iostream>
#include <string.h>
#include "Client.h"
#include <unistd.h>
#include  <chrono>
#include <cstring>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

using namespace std;
using namespace chrono;
// using namespace this_thread;

void helloserver(void){
    printf("hello server ...\n"); fflush(stdout);
}
int main(int argc, char *argv[])
{
    //string m;
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
	std::cout<<hostbuffer<<std::endl;

    c1.GetHost("127.0.0.1", 2020);
    cout<<"HOST\n";
    c1.ClientConnect();
    
    //m = "hello s   haha";
    strcpy(buffer, "hello s   haha");
    cout<<buffer<<endl;
    c1.ClientWrite(buffer);
    for(int i = 0; i<1000000; i++);
    sleep(5);
    c1.ClientRead(buffer);
    cout<<buffer<<endl;
    cout<<"Finish\n";
    
    return 0;
}
