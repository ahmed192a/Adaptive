#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>

#include "ara/com/ServiceDiscovery/csv.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "color/color.hpp"
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include <pthread.h>

#define CSV_FILE "data.csv"

using namespace std;
int portNumber = 1690;
SD_data receive;
CSV csv;
void *pthread0(void *);
void *pthread1(void *);
int main()
{

    cout << "SD\n";

    pthread_t threads[2];
    int i = 0;

    csv.clear(CSV_FILE);
    // use the child process for sercice discovery (Listen to all servers and get services information)
    int th1 = pthread_create(&threads[0], NULL, pthread0, (void *)&i);
    if (th1)
    {
        cout << "ERRor" << th1 << endl;
        exit(-1);
    }
    i = 1;
    int th2 = pthread_create(&threads[1], NULL, pthread1, (void *)&i);
    if (th2)
    {
        cout << "ERRor" << th2 << endl;
        exit(-1);
    }

    pthread_exit(NULL);

    return 0;
}

void *pthread1(void *)
{
    vector<SD_data> data;
    // wait until a client request a service
    // if a client requests a service,  search the csv file to find this service
    CServer s1(SOCK_STREAM);
    int service_id;
    s1.OpenSocket(portNumber);
    s1.BindServer();
    s1.ListenServer(3);
    while (1)
    {
        uint32_t _size = 0;
        std::vector<uint8_t> _msg;
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage R_msg;

        Socket soc = s1.AcceptServer();

        // receive the service id
        soc.Receive(&_size, sizeof(_size));
        _msg.reserve(_size);
        soc.Receive(&_msg[0], _size);
        sd_msg.Deserialize(_msg);
        // Loop on entries
        auto entry = sd_msg.Entries()[0];
        uint32_t serviceid = entry->ServiceId();
        ara::com::entry::ServiceEntry eventgroup_entry = ara::com::entry::ServiceEntry::CreateFindServiceEntry(serviceid);

        std::cout << "[SD] client requested service id  : " << serviceid << std::endl;

        // search the file,
        // it takes a vector of structs "in case there's more than one server offers the service"
        csv.FindRow(CSV_FILE, serviceid, data);
        // for (auto i : data)
        // {
            cout << "process id : " << data[0].process_id << endl;
            cout << "service id : " << data[0].service_id << endl;
            cout << "port number : " << data[0].port_number << endl;
            // create dynamic Ipv4EndpointOption object from static function
            ara::com::option::Ipv4EndpointOption ipv4_option = ara::com::option::Ipv4EndpointOption::CreateSdEndpoint(false, ara::com::helper::Ipv4Address(127, 0, 0, 1), ara::com::option::Layer4ProtocolType::Udp, data[0].port_number);

            eventgroup_entry.AddFirstOption(&ipv4_option);
        // }

        R_msg.AddEntry(&eventgroup_entry);
        std::vector<uint8_t> R_msg_serialized = R_msg.Serializer();
        uint32_t R_msg_size = R_msg_serialized.size();

        // in the future, a number should be sent first to indicate how many struct is gonna be sent
        // then a for loop to send the vector "containing port numbers" element by element

        // send the struct to the client
        soc.Send(&R_msg_size, sizeof(R_msg_size));
        soc.Send(&R_msg_serialized[0], R_msg_size);
        soc.CloseSocket();
    }

    s1.CloseSocket();

}

void *pthread0(void *)
{
    // listen to all servers
    // save process id, service id, and port number into the csv file
    CServer s1(SOCK_DGRAM);
    s1.OpenSocket(portNumber);
    s1.BindServer();

    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    while (1)
    {
        uint32_t _size = 0;
        std::vector<uint8_t> _msg;
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
        // receive a struct containing the service information
        s1.UDPRecFrom(&_size, sizeof(_size), (struct sockaddr *)&cliaddr, &len);
        _msg.reserve(_size);
        s1.UDPRecFrom(&_msg[0], _size, (struct sockaddr *)&cliaddr, &len);
        // s1.UDPRecFrom(&receive, sizeof(SD_data), (struct sockaddr *)&cliaddr, &len);
        // data.push_back(receive);
        cout << "[SD] : receiving offers" << endl;
        cout << "size is " << _size << endl;
        sd_msg.Deserialize(_msg);
        // Loop on entries
        auto entrie = sd_msg.Entries();
        for (auto entry : entrie)
        {
            switch (entry->Type())
            {
            case ara::com::entry::EntryType::Finding:
            {
                cout << "EntryType: Finding" << endl;
                // uint32_t _service_id = entry->ServiceId();
                // uint32_t _instance_id = entry->InstanceId();
            }
            break;
            case ara::com::entry::EntryType::Offering:
            {
                cout << "EntryType: Offering" << endl;
                auto first_option = entry->FirstOptions()[0];
                ara::com::option::Ipv4EndpointOption *ipv4_option = (ara::com::option::Ipv4EndpointOption *)first_option;
                cout << "IPv4: " << int(ipv4_option->IpAddress().Octets[0]) << "." << int(ipv4_option->IpAddress().Octets[1]) << "." << int(ipv4_option->IpAddress().Octets[2]) << "." << int(ipv4_option->IpAddress().Octets[3]) << endl;
                cout << "Port: " << ipv4_option->Port() << endl;
                cout << "ServiceId: " << entry->ServiceId() << endl;
                // uint16_t _port = ipv4_option->Port();
                // uint32_t _service_id = entry->ServiceId();
                // uint32_t _instance_id = entry->InstanceId();
                // place info into recvieve object
                receive.process_id = entry->InstanceId();
                receive.service_id = entry->ServiceId();
                receive.port_number = ipv4_option->Port();
                // save the information into the csv file
                // check TTL
                if (entry->TTL() > 0)
                {
                    csv.write(CSV_FILE, receive);
                }
                else
                {
                    cout << "TTL is 0" << endl;
                    csv.delete_record(CSV_FILE, receive.service_id);
                }
            }
            break;
            case ara::com::entry::EntryType::Subscribing:
            {
                cout << "EntryType: Subscribing" << endl;
            }
            break;

            case ara::com::entry::EntryType::Acknowledging:
            {
            }
            break;
            }
        }
    }
    s1.CloseSocket();
}