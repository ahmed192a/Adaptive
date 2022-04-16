#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/ipc/client/socket_Client.hpp"

#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"
#include "ara/com/SOMEIP/option/option.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/SOMEIP/entry/service_entry.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ara::com::entry;
using namespace ara::com::SOMEIP_MESSAGE;
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
    Message BGMG = Message::Deserialize(v);
    cout<<"Message ID "<<BGMG.MessageId().serivce_id<<endl;
    cout<<"Message ID "<<BGMG.MessageId().method_id<<endl;
    // print length
    cout<<"Message Length "<<BGMG.Length()<<endl;
    // clinet id
    cout<<"Request ID "<<BGMG.ClientId()<<endl;
    // session id
    cout<<"Session ID "<<BGMG.SessionId()<<endl;
    // protocol version
    cout<<"Protocol Version "<<(int)BGMG.ProtocolVersion()<<endl;
    // interface version
    cout<<"Interface Version "<<(int)BGMG.InterfaceVersion()<<endl;
    // message type
    cout<<"Message Type "<<(int)BGMG.Messagetype()<<endl;
    // return code
    cout<<"Return Code "<<(int)BGMG.Returncode()<<endl;

    int x = BGMG.getload()[0];
    cout<<"x is "<<x<<endl;
    x = BGMG.getload()[1];
    cout<<"x is "<<x<<endl;
    x = BGMG.getload()[2];
    cout<<"x is "<<x<<endl;
    x = BGMG.getload()[3];  
    cout<<"x is "<<x<<endl;





    // GBSD.setdata(v);
    /*
    GBSD.Deserialize(v);
    cout<<"Length of message " <<GBSD.Length()<<endl;

    std::vector<Entry *> entries = GBSD.Entries();
    for (std::vector<Entry *>::iterator it = entries.begin(); it != entries.end(); it++)
    {
        if((*it)->Type() == EntryType::Finding){
            cout<<"Service id " <<(*it)->ServiceId()<<endl;
            cout<<"Instance id "<<(*it)->InstanceId()<<endl;
            cout<<"TTL "<<(*it)->TTL()<<endl;
            // cout<<"Minor version "<<(*it)->MinorVersion()<<endl;
        }
        if((*it)->Type() == EntryType::Offering){
            std::vector<Option *> options = (*it)->FirstOptions();
            for (std::vector<Option *>::iterator itt = options.begin(); itt != options.end(); itt++)
            {
                // if((*itt)->Type() == OptionType::IPv4Endpoint)
                {
                    Ipv4EndpointOption *ipv4 = (Ipv4EndpointOption *)(*itt);
                    int xxx = ipv4->IpAddress().Octets[0]; 
                    int yyy = ipv4->IpAddress().Octets[1];
                    int zzz = ipv4->IpAddress().Octets[2];
                    int www = ipv4->IpAddress().Octets[3]; 
                    cout<<"xxx "<<xxx<<endl;
                    cout<<"yyy "<<yyy<<endl;
                    cout<<"zzz "<<zzz<<endl;
                    cout<<"www "<<www<<endl;
                    cout<<"Port "<<ipv4->Port()<<endl;
                }
            }
        }
        if((*it)->Type() == EntryType::Subscribing)
        {
            cout<<"Service id " <<(*it)->ServiceId()<<endl;
            cout<<"Instance id "<<(*it)->InstanceId()<<endl;
            cout<<"TTL "<<(*it)->TTL()<<endl;
            int major = (*it)->MajorVersion();
            cout<<"Major version "<<major<<endl;
            EventgroupEntry *event = (EventgroupEntry *)(*it);
            cout<<"EventgroupId id "<<event->EventgroupId()<<endl;
        }

    }
*/


    // uint32_t x;
    // uint16_t y = (v[0]<<8) | v[1];
    // uint16_t z = (v[2]<<8) | v[3];
    // printf("%d\n", y);
    // printf("%d\n", z);



    return 0;
}