#include "ara/com/ipc/server/socket_Server.hpp"
#include <iostream>
#include <vector>
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/SOMEIP/entry/service_entry.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include <unistd.h>
using namespace std;
using namespace ara::com::entry;
using namespace ara::com::SOMEIP_MESSAGE::sd;
using namespace ara::com::option;
using namespace ara::com::helper;
SomeIpSDMessage GBSD;
// ServiceEntry GBSE=ServiceEntry::CreateFindServiceEntry (1,2,3,10,11);
// ServiceEntry GBSE = ServiceEntry::CreateOfferServiceEntry (1, 3, 10, 11);
// ServiceEntry GBSE = ServiceEntry::CreateStopOfferEntry (1, 3, 10, 11);
EventgroupEntry GBSE = EventgroupEntry::CreateSubscribeEventEntry (1, 3, 10, 11);
// EventgroupEntry GBSE = EventgroupEntry::CreateUnsubscribeEventEntry (1, 3, 10, 11);


//false => repeated
Ipv4EndpointOption GBIP = Ipv4EndpointOption::CreateSdEndpoint(false, Ipv4Address(127, 0, 0, 1), Layer4ProtocolType::Udp, 2025);

struct sockaddr_in sd;

void write(CServer &fd ,const vector<uint8_t> &arg)
{
    uint32_t size = arg.size();
    cout<<"Write Size "<<size<<endl;
    fd.UDPSendTo(&size, sizeof(size), ( sockaddr *)&sd);
    fd.UDPSendTo((void*)arg.data(), arg.size(), ( sockaddr *)&sd) ;
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
    cout<<"Service id " <<GBSD.MessageId().serivce_id<<endl;
    cout<<"method id "<<GBSD.MessageId().method_id<<endl;
    cout<<"Length of message " <<GBSD.Length()<<endl;

    return 0;
}



