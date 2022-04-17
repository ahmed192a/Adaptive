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
#define CSV_FILE "data.csv"

using namespace std;

int main()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    cout << red<<"SD\n";
    // cout << "This ->" << red << serverP << def << "<- is red." << endl;

    int portNumber = 1690;
    int process_id = fork();
    vector<SD_data> data;
    SD_data receive;
    CSV csv;

    uint32_t _size= 0;
    std::vector<uint8_t> _msg;
    ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;

    csv.clear(CSV_FILE);
    // use the child process for sercice discovery (Listen to all servers and get services information)
    if (process_id == 0)
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

            // receive a struct containing the service information
            s1.UDPRecFrom(&_size, sizeof(_size), (struct sockaddr *) &cliaddr, &len);
            _msg.reserve(_size);
            s1.UDPRecFrom(&_msg[0], _size, (struct sockaddr *) &cliaddr, &len);
            // s1.UDPRecFrom(&receive, sizeof(SD_data), (struct sockaddr *)&cliaddr, &len);
            // data.push_back(receive);
            cout << red << "[SD] : receiving offers" << endl;
            cout << "size is " << _size << endl;
            sd_msg.Deserialize(_msg);
            // Loop on entries
            auto entrie = sd_msg.Entries();
            for( auto entry : entrie)
            {
                switch(entry.Type())
                {
                    case ara::com::entry::EntryType::Finding:
                        cout << "EntryType: Finding" << endl;
                        uint32_t _service_id = entry.ServiceId();
                        uint32_t _instance_id = entry.InstanceId();
                        
                        break;
                    case ara::com::entry::EntryType::Offering:
                        cout << "EntryType: Offering" << endl;
                        auto first_option = entry.FirstOptions()[0];
                        Ipv4EndpointOption * ipv4_option = (Ipv4EndpointOption *) option;
                        cout << "IPv4: " << int(ipv4_option->Address().Octets[0] )<<  "." <<  int(ipv4_option->Address().Octets[1]) << "." << int(ipv4_option->Address().Octets[2]) << "." << int(ipv4_option->Address().Octets[3]) << endl;
                        cout << "Port: " << ipv4_option->Port() << endl;
                        uint16_t _port = ipv4_option->Port();
                        uint32_t _service_id = entry.ServiceId();
                        uint32_t _instance_id = entry.InstanceId();
                        break;
                    case ara::com::entry::EntryType::Subscribing:
                        cout << "EntryType: Subscribing" << endl;
                        break;
                    case ara::com::entry::EntryType::Acknowledging:
                    break;
                }
                

            }
               
            cout << red << "[SD] : Struct: " << receive.port_number << "-" << receive.service_id << "-" << receive.process_id << endl;
            // write these information into the csv file

            if (receive.message_type)
                csv.write(CSV_FILE, data[0]);
            else
                csv.delete_record(CSV_FILE, receive.service_id);
        }
        s1.CloseSocket();
    }
    // use the main process for service registery (Listen to all clients and provide them info if exists)
    else
    {
        // wait until a client request a service
        // if a client requests a service,  search the csv file to find this service
        CServer s1(SOCK_STREAM);
        int service_id;
        s1.OpenSocket(portNumber);
        s1.BindServer();
        s1.ListenServer(3);
        while (1)
        {

            Socket soc = s1.AcceptServer();
            // receive the service id
            soc.Receive(&service_id, sizeof(int));
            std::cout<<"[SD] client requested service id  : "<<service_id<<std::endl;

            // search the file,
            // it takes a vector of structs "in case there's more than one server offers the service"
            csv.FindRow(CSV_FILE, service_id, data);

            // in the future, a number should be sent first to indicate how many struct is gonna be sent
            // then a for loop to send the vector "containing port numbers" element by element

            // send the struct to the client
            soc.Send(&data[0], sizeof(SD_data));
            soc.CloseSocket();
        }

        s1.CloseSocket();

        waitpid(process_id, NULL, 0);

        // while(wait(NULL) > 0){}
    }

    return 0;
}
