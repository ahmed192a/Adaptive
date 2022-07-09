/**
 * @file service_descovery.cpp
 * @brief 
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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
#include <pthread.h>

#include "ara/com/ServiceDiscovery/csv.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include "ara/exec/execution_client.hpp"

#define CSV_FILE "data.csv"

using namespace std;
using namespace ara::exec;

//// Functions declarations
void  handle_sigterm(int sig);  
void *pthread0(void *); 
void *pthread1(void *);

//// Globale variables
int sigval = 0;
int portNumber = 1690;
SD_data receive; // global variable to store the data received from the server
CSV   csv;
ExecutionClient client;

/**
 * @brief main function of service discovery
 * 
 * @return int 
 */
int main()
{
    cout<<endl<<"[SD]"<<std::string(get_current_dir_name())<<endl;
    cout << "SD"<<endl;
    signal(SIGTERM, handle_sigterm);
    client.ReportExecutionState(ExecutionState::kRunning);

    pthread_t threads[2]; // create two threads
    int i = 0;            // thread number

    csv.clear(CSV_FILE); // clear the csv file before starting the program

    int th1 = pthread_create(&threads[0], NULL, pthread0, (void *)&i); // create thread 0 to receive data from the server
    if (th1)
    {
        cout << "ERROR" << th1 << endl;
        exit(-1);
    }
    i = 1;
    int th2 = pthread_create(&threads[1], NULL, pthread1, (void *)&i); // create thread 1 to listen to the clients
    if (th2)
    {
        cout << "ERROR" << th2 << endl;
        exit(-1);
    }

    pthread_exit(NULL);

    return 0;
}


/////// Functions definitions
/**
 * @brief Signal handler for SIGTERM
 * @param sig signal number
 * @return void
 */
void handle_sigterm(int sig){
    sigval = 1;                                 // set signal value will be used as flag
    cout<<"{SD} terminating"<<endl;            
    client.ReportExecutionState(ExecutionState::kTerminating);
    exit(0);
}


/**
 * @brief listen to all clients and find the requested service
 * @return void* 
 */
void *pthread1(void *)
{
    cout<<"[SD] thread 1 is running"<<endl;
    CServer s1(SOCK_STREAM);   // create a server object
    int service_id;            // service id
    s1.OpenSocket(portNumber); // open a socket on port 1690
    s1.BindServer();           // bind the server to the port
    s1.ListenServer(3);        // listen to the port
    while (1)
    {
        vector<SD_data> data;      // vector to store the data from the csv file
        uint32_t _size = 0;
        std::vector<uint8_t> _msg;                            // vector to store the serialized message
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg; // create a SomeIP SD message to store the deserialized message received from the client
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage R_msg;  // create a SomeIP SD message to send the message to the client

        Socket soc = s1.AcceptServer(); // accept the client connection

        // read the message from the client
        soc.Receive(&_size, sizeof(_size)); // receive the size of the message
        _msg.reserve(_size);                // reserve memory for the message
        soc.Receive(&_msg[0], _size);       // receive the message
        sd_msg.Deserialize(_msg);           // deserialize the message

        // Loop on entries
        auto entry = sd_msg.Entries()[0];        // get the first entry
        uint32_t serviceid = entry->ServiceId(); // get the service id
        ara::com::entry::ServiceEntry eventgroup_entry = ara::com::entry::ServiceEntry::CreateFindServiceEntry(serviceid); // get the service entry

        std::cout << "[SD] client requested service id  : " << serviceid << std::endl; // print the service id

        csv.FindRow(CSV_FILE, serviceid, data); // search the file for the service id
        // for (auto i : data)
        // {
            cout << "instance id : " << data[0].instance_id << endl; // print the instance id
            cout << "service id : " << data[0].service_id << endl;   // print the service id
            cout << "port number : " << data[0].port_number << endl; // print the port number

            // create dynamic Ipv4EndpointOption object from static function
            ara::com::option::Ipv4EndpointOption ipv4_option = ara::com::option::Ipv4EndpointOption::CreateSdEndpoint(false, ara::com::helper::Ipv4Address(127, 0, 0, 1), ara::com::option::Layer4ProtocolType::Udp, data[0].port_number);

            eventgroup_entry.AddFirstOption(&ipv4_option); // add the ipv4 option to the eventgroup entry
        // }

        R_msg.AddEntry(&eventgroup_entry);                          // add the eventgroup entry to the SomeIP SD message
        std::vector<uint8_t> R_msg_serialized = R_msg.Serializer(); // serialize the SomeIP message
        uint32_t R_msg_size = R_msg_serialized.size();              // get the size of the serialized message

        soc.Send(&R_msg_size, sizeof(R_msg_size));  // send the size of the message
        soc.Send(&R_msg_serialized[0], R_msg_size); // send the message
        
        soc.CloseSocket(); // close the socket 
    }

    s1.CloseSocket(); // close the socket

}

/**
 * @brief listen to all servers and get services information
 * @return void* 
 */
void *pthread0(void *)
{
    cout<<"[SD] thread 0 is running"<<endl;
    CServer s1(SOCK_DGRAM);    // create a server object
    s1.OpenSocket(portNumber); // open a socket on port 1690
    s1.BindServer();           // bind the server to the port

    struct sockaddr_in cliaddr;      // create a struct to store the client address
    socklen_t len = sizeof(cliaddr); // create a variable to store the size of the client address   
    while (1)
    {
        uint32_t _size = 0;        // create a variable to store the size of the message
        std::vector<uint8_t> _msg; // create a vector to store the received message

        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg; // create a SomeIP SD message to store the deserialized message received from the server
        
        s1.UDPRecFrom(&_size, sizeof(_size), (struct sockaddr *)&cliaddr, &len); // receive the size of the message
        _msg.reserve(_size);                                                     // reserve memory for the message
        s1.UDPRecFrom(&_msg[0], _size, (struct sockaddr *)&cliaddr, &len);       // receive the message

        cout << "[SD] : receiving offers" << endl; 
        cout << "size is " << _size << endl; // print the size of the message
        sd_msg.Deserialize(_msg);            // deserialize the message

        // Loop on entries
        auto entrie = sd_msg.Entries(); // get the entries
        for (auto entry : entrie)
        {
            switch (entry->Type())
            {
            case ara::com::entry::EntryType::Finding:
            {
                cout << "EntryType: Finding" << endl;
            }
            break;
            case ara::com::entry::EntryType::Offering:
            {
                cout << "EntryType: Offering" << endl;

                auto first_option = entry->FirstOptions()[0]; // get the first entry option

                ara::com::option::Ipv4EndpointOption *ipv4_option = (ara::com::option::Ipv4EndpointOption *)first_option; // store first option as ipv4 option
                
                // print the ipv4 address
                cout << "IPv4: " << int(ipv4_option->IpAddress().Octets[0]) << "." << int(ipv4_option->IpAddress().Octets[1]) << "." << int(ipv4_option->IpAddress().Octets[2]) << "." << int(ipv4_option->IpAddress().Octets[3]) << endl;
                cout << "Port: " << ipv4_option->Port() << endl;     // print the port number
                cout << "ServiceId: " << entry->ServiceId() << endl; // print the service id

                // place info into recvieve object
                receive.instance_id = entry->InstanceId(); // store the instance id
                receive.service_id = entry->ServiceId();   // store the service id
                receive.port_number = ipv4_option->Port(); // store the port number

                // check TTL
                if (entry->TTL() > 0)
                {
                    csv.write(CSV_FILE, receive); // write the service info in the csv file
                }
                else
                {
                    cout << "TTL is 0" << endl;
                    csv.delete_record(CSV_FILE, receive.service_id, receive.instance_id); // delete the service record from the csv file
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
    s1.CloseSocket(); // close the socket
}