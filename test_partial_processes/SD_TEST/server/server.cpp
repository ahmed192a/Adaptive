#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <memory>

#include "ara/SD_s/skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/deserializer.hpp"
#include "color/color.hpp"

#define SERVER_PORT 5365
#define SD_PORT 1690
#define MAX_QUEUE_CLIENTS 5
#define SERVICE_ID 32

using namespace std;
using C_Info = ara::com::proxy_skeleton::C_Info;
// using event_info = ara::com::proxy_skeleton::event_info;

CServer server_main_socket(SOCK_STREAM);   // Socket between the server and the client
CServer server_main_socket_DG(SOCK_DGRAM); // Socket between the server and the client
ara::com::InstanceIdentifier instance(SERVICE_ID); 
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle{SERVER_PORT, SD_PORT};
skeleton server_skeleton_obj(instance, skeleton_handle);

Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);


void Handle_IO(int sigtype);

int main(int argc, char **argv)
{
    /// VARIABLES
    char buffer[256];
    C_Info x;
    std::vector<uint8_t> msg;
    int msg_size;
    ara::com::Deserializer dser;

    // We take the sever port number as the first argument
    cout << blue << "\t[SERVER] mypid: " << getpid() << endl;

    // g_handler = &subscribe_handler2;
    // ara::com::proxy_skeleton::skeleton::EVENT::set_handle(&subscribe_handler2);
    /* TCP with client */
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    server_main_socket_DG.OpenSocket(SERVER_PORT);
    server_main_socket_DG.BindServer();

    // send to service discovery the offered service
    server_skeleton_obj.OfferService();

    if (server_main_socket_DG.EnableInterrupt(Handle_IO) == FAILED)
    {
        cout << "int errrrrrrrrrrrror\n";
        return -1;
    }
    cout << blue << "\t[SERVER]  Ready" << endl;
    Socket Sclient = server_main_socket.AcceptServer();
    cout << blue << "\t[SERVER]  accepted" << endl;

    strcpy(buffer, "=> Server connected...\n");

    // send a confirmation connect to client
    Sclient.Send(buffer, strlen(buffer));

    // Receive a struct from client containing the method name and parameters
    Sclient.Receive((void *)&msg_size, sizeof(msg_size));
    msg.resize(msg_size);
    Sclient.Receive((void *)&msg[0], sizeof(msg));

    // Sclient.Receive((void *)&x, sizeof(x));

    // print the requested method
    // cout << blue << "\t[SERVER] " << x.method_name << endl;

    // Perform the requested method then send the result
    server_skeleton_obj.method_dispatch(msg, Sclient);

    /////////////////////////////////////////////////////////////////////////////////////
    while (server_skeleton_obj.event1.getsub().empty())
    {
    }
    std::cout << blue << "\t[SERVER] : ";
    server_skeleton_obj.event1.update(7);

    sleep(1);
    while (server_skeleton_obj.event2.getsub().empty())
    {
    }
    std::cout << blue << "\t[SERVER] : ";

    server_skeleton_obj.event2.update(9);

    int y = 2;
    while (server_skeleton_obj.field1.getsub().empty())
    {
    }

    std::cout << blue << "\t[SERVER] : ";
    server_skeleton_obj.field1.update(y);

    while (!server_skeleton_obj.field1.getsub().empty()) // test uns
    {
    }

    cout << blue << "\n\t[SERVER] Goodbye..." << endl;

    // server_skeleton_obj.StopOfferService();

    // always be awake to receive stuff from signal
    while (1)
    {
        printf(".\n");
        sleep(1);
    }

    server_main_socket.CloseSocket();
    return 0;
}



void Handle_IO(int sigtype)
{
    static uint8_t IO_Handler_count =0;

    if(IO_Handler_count == 1)
    {
        IO_Handler_count = 0;
        return;
    }
    

    sockaddr_in echoClntAddr; /* Address of datagram source */
    unsigned int clntLen=sizeof(echoClntAddr);     /* Address length */
    ara::com::proxy_skeleton::event_info evr;
    std::vector<uint8_t> msg;
    server_main_socket_DG.UDPRecFrom((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr, &clntLen);

    printf("\n[SERVER]  ->> Handling client %s %d with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), echoClntAddr.sin_port,evr.data_size);fflush(stdout);
    msg.resize(evr.data_size);
    if(evr.data_size)
    {
        IO_Handler_count++;
        server_main_socket_DG.UDPRecFrom((void *)&msg[0], evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
    }
    
    ara::com::proxy_skeleton::Client_udp_Info cudp;
    cudp.port = echoClntAddr.sin_port;
    cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));

    switch (evr.service_id)
    {
    case SERVICE_ID:
        switch (evr.event_id)
        {
        case 0:
            std::cout << "[server] sub event1 start\n";
            server_skeleton_obj.event1.handlecall(evr, cudp);
            std::cout << "[server] sub event1 start\n";

            break;
        case 1:
            std::cout << "[server] sub event2 start\n";
            server_skeleton_obj.event2.handlecall(evr, cudp);
                        std::cout << "[server] sub event2 start\n";

            break;
        case 2:
            server_skeleton_obj.field1.handlecall(evr,msg, cudp);
            if (evr.operation == 4)
            {
                std::cout << "[server] get field1 " << std::endl;
                server_main_socket_DG.UDPSendTo((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr);
            }
            else if (evr.operation == 3)
            {
                std::cout << "[server] set field1 " << std::endl;
            }
            else
            {
                std::cout << "[server] sub field1 start\n";
            }
            break;

        default:
            break;
        }
        break;
    default:
        break;
    }
}