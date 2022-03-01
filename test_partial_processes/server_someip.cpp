#include "../src/ara/com/ipc/server/socket_Server.h"


#include <iostream>
#include "ara/com/SOMEIP_MESSAGE/sd/SomeipSDMessage.h"
#include<vector>
#include"ara/com/option/ipv4_endpoint_option.h"
#include"ara/com/helper/service_entry.h"
using namespace std;
using namespace ara::com::entry;
using namespace ara::com::SOMEIP_MESSAGE::sd;
using namespace ara::com::option;
using namespace ara::com::helper;
SomeIpSDMessage GBSD;
ServiceEntry GBSE=ServiceEntry::CreateFindServiceEntry (1,2,3,10,11);
Ipv4EndpointOption GBIP= Ipv4EndpointOption::CreateSdEndpoint(false,Ipv4Address(1,2,3,4),Layer4ProtocolType::Udp,2154);


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
    GBSE.AddFirstOption(&GBIP);
    GBSD.AddEntry(&GBSE);
    vector<uint8_t>payload=GBSE.Payload();
    servertest.UDPSendTo(&payload, sizeof(payload), (const sockaddr *)&sd);
    int x;
    cin>>x;
    return 0;
}



