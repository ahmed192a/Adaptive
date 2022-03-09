#include "../src/ara/com/ipc/server/socket_Server.h"
#include "../src/ara/com/ipc/client/socket_Client.h"

#include <iostream>
#include <vector>
using namespace std;
struct sockaddr_in cliaddr;
socklen_t len = sizeof(cliaddr);


void read(CServer &fd, vector<uint8_t> &arg)
{
    uint32_t size;
    size_t i;
    uint8_t data;
    fd.UDPRecFrom(&size, sizeof(size), (struct sockaddr *) &cliaddr, &len);
    cout<<"size is "<<size<<endl;
    arg.reserve(size);
    fd.UDPRecFrom(&arg[0], size, (struct sockaddr *) &cliaddr, &len);

    // for (i = 0; i < size; i++)
    // {
    //     fd.UDPRecFrom(&data, sizeof(data), (struct sockaddr *) &cliaddr, &len);
    //     arg.push_back(data);
    // }
}

int main()
{
    CServer clienttest(SOCK_DGRAM);
    clienttest.OpenSocket(2033);
    clienttest.BindServer();

    vector<uint8_t>v;
    read(clienttest, v);

    // v.reserve(1);

    // uint32_t size;
    // cout<<"client receive 1\n";
    // clienttest.UDPRecFrom(&size, sizeof(size), (struct sockaddr *) &cliaddr, &len);
    // fullmsg = new uint8_t[size];
    // cout<<"client receive 2\n";
    // clienttest.UDPRecFrom(&v[0], 1, (struct sockaddr *) &cliaddr, &len);
    // cout<<"client convert \n";


    //cout<<fullmsg[0]<<endl;

    uint32_t x;// = (fullmsg[0]<<24) | (fullmsg[1]<<16) | (fullmsg[2]<<8) | (fullmsg[3]);
    
    //cout<<v[0]<<endl;
    uint16_t y = (v[0]<<8) | v[1];
    uint16_t z = (v[2]<<8) | v[3];
    printf("%d\n", y);
    printf("%d\n", z);
    //cout<<"x : "<<x<<endl;

    cin>>x;

    //sd.sa_data;

    return 0;
}