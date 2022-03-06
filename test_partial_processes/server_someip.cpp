#include "../src/ara/com/ipc/server/socket_Server.h"
#include <iostream>
#include <vector>
#include "../src/ara/com/SOMEIP/SomeipSDMessage.h"
#include "../src/ara/com/SOMEIP/option/ipv4_endpoint_option.h"
#include "../src/ara/com/SOMEIP/helper/ipv4_address.h"
#include "../src/ara/com/SOMEIP/entry/service_entry.h"
#include <unistd.h>
using namespace std;
using namespace ara::com::entry;
using namespace ara::com::SOMEIP_MESSAGE::sd;
using namespace ara::com::option;
using namespace ara::com::helper;
SomeIpSDMessage GBSD;
ServiceEntry GBSE=ServiceEntry::CreateFindServiceEntry (1,2,3,10,11);
Ipv4EndpointOption GBIP= Ipv4EndpointOption::CreateSdEndpoint(false,Ipv4Address(1,2,3,4),Layer4ProtocolType::Udp,2154);

struct sockaddr_in sd ;

void write(CServer &fd ,const vector<uint8_t> &arg)
{
    uint32_t size = arg.size();
    cout<<size<<endl;
    fd.UDPSendTo(&size, sizeof(size), (const sockaddr *)&sd);
    fd.UDPSendTo((const char*)arg.data(), arg.size(), (const sockaddr *)&sd) ;
    // for (vector<uint8_t>::const_iterator it = arg.begin(); it != arg.end(); it++)
    // {
    //     fd.UDPSendTo(&(*it), sizeof(uint8_t), (const sockaddr *)&sd) ;
    // }
}
int main()
{
    
    cout<<"server"<<endl;
    CServer servertest(SOCK_DGRAM);
    servertest.OpenSocket(2025);
    servertest.BindServer();
    sd.sin_family = AF_INET; // IPv4
    sd.sin_addr.s_addr = INADDR_ANY;
    sd.sin_port = htons(2033);
    char buffer [] = "some ip message";
    cout<<"add option\n";
    GBSE.AddFirstOption(&GBIP);
    cout<<"add entry\n";
    GBSD.AddEntry(&GBSE);
    cout<<"get payload\n";
    vector<uint8_t>payload=GBSD.Payload();

    write(servertest, payload);
    cout<<GBSD.MessageId().serivce_id<<endl;
    cout<<GBSD.MessageId().method_id<<endl;

    // uint32_t size = GBSD.Length() ;


    // cout<<size<<endl;
    // std::string s(payload.begin(), payload.end());
    // vector<uint8_t>v;
    // v.reserve(1);
    // v[0]=1;
    // servertest.UDPSendTo(&size, sizeof(size), (const sockaddr *)&sd);
    // //sleep(1);
    // servertest.UDPSendTo(&v[0], sizeof(v[0]), (const sockaddr *)&sd);
   

    int x;
    cin>>x;
    return 0;
}



