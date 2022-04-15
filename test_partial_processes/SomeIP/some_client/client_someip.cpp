#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/ipc/client/socket_Client.hpp"

#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/SOMEIP/entry/service_entry.hpp"

#include <iostream>
#include <vector>
using namespace std;
using namespace ara::com::entry;
using namespace ara::com::SOMEIP_MESSAGE::sd;
using namespace ara::com::option;
using namespace ara::com::helper;

struct sockaddr_in cliaddr;
socklen_t len = sizeof(cliaddr);


SomeIpSDMessage GBSD;



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
    // GBSD.setdata(v);
    GBSD.Deserialize(v);
    cout<<"Length of message " <<GBSD.Length()<<endl;
    // cout<<"Length of entry " <<GBSD.getEntriesLength()<<endl;
    // cout<<"Length of option " <<GBSD.getOptionsLength()<<endl;
    // std::vector<Entry *> entries = GBSD.Entries();
    // for (std::vector<Entry *>::iterator it = entries.begin(); it != entries.end(); it++)
    // {
    //     cout<<"Service id " <<(*it)->ServiceId()<<endl;
    //     cout<<"Instance id "<<(*it)->InstanceId()<<endl;
    // }



    // uint32_t x;
    // uint16_t y = (v[0]<<8) | v[1];
    // uint16_t z = (v[2]<<8) | v[3];
    // printf("%d\n", y);
    // printf("%d\n", z);



    return 0;
}