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

#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/deserializer.hpp"
#include "ara/SD_s/skeleton.hpp"
#include "ara/com/SOMEIP/Message.hpp"
#include "ara/ucm/pkgmgr/packet.hpp"

#include <sys/mman.h>
#include <sys/ipc.h>

#define SERVER_PORT 5365
#define SD_PORT 1690
#define MAX_QUEUE_CLIENTS 5
#define SERVICE_ID 45
#define NUM_THREADS 3

using namespace std;
using namespace ara::ucm::pkgmgr::skeleton;

// Socket for methods
// Socket for events
CServer server_main_socket_DG(SOCK_DGRAM);

ara::com::InstanceIdentifier instance(SERVICE_ID);
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle{SERVER_PORT, SD_PORT};
// PackageManagementSkeleton server_skeleton_obj(instance, skeleton_handle);

std::shared_ptr<PackageManagementSkeleton> server_skeleton_ptr = std::make_shared<PackageManagementSkeleton>(instance, skeleton_handle);

bool stop = true;

void Handle_IO();
void *pthread0(void *v_var);
void *pthread1(void *v_var);
void *pthread2(void *v_var);



int main()
{
    pthread_t threads[NUM_THREADS];

    int th1, th2;
    int i = 0;

    th1 = pthread_create(&threads[0], NULL, pthread0, (void *)&i);
    if (th1)
    {
        cout << "ERRor" << th1 << endl;
        exit(-1);
    }
    i = 1;
    th2 = pthread_create(&threads[1], NULL, pthread1, (void *)&i);
    if (th2)
    {
        cout << "ERRor" << th2 << endl;
        exit(-1);
    }

    pthread_exit(NULL);

    return 0;
}

void *pthread0(void *v_var)
{
    CServer server_main_socket(SOCK_STREAM);

    /// VARIABLES
    char buffer[256];
    // ara::com::proxy_skeleton::C_Info x;
    // std::vector<uint8_t> msg;
    int msg_size;
    ara::com::Deserializer dser;

    // We take the sever port number as the first argument
    cout << "\t[SERVER] mypid: " << getpid() << endl;
    /* TCP with client */
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    server_skeleton_ptr->OfferService();

    cout << "shared " << server_skeleton_ptr << endl;
    cout << "\t[SERVER]  Ready" << endl;

    while (1)
    {
        Socket Sclient = server_main_socket.AcceptServer();
        cout << "\t[SERVER]  accepted" << endl;
        // strcpy(buffer, "=> Server connected...\n");

        // send a confirmation connect to client
        // Sclient.Send(buffer, strlen(buffer));

        // Receive a struct from client containing the method name and parameters
        std::vector<uint8_t> msg;
        Sclient.Receive((void *)&msg_size, sizeof(msg_size));
        msg.resize(msg_size);
        Sclient.Receive((void *)&msg[0], msg_size);


        
        cout << "\t[SERVER]  received" << endl;
        ara::com::SOMEIP_MESSAGE::Message someip_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg);

        
        if (someip_msg.check_Methode_ID() == true)
        {
            cout << "This is method request " << endl;
            server_skeleton_ptr->method_dispatch(someip_msg, Sclient);
        }
        else
        {
            cout << "This is SET OR GET request" << endl;
            server_skeleton_ptr->field_method_dispatch(someip_msg, Sclient);
        }

    }

    // always be awake to receive stuff from signal
    while (stop)
    {
        printf(".\n");
        sleep(1);
    }

    server_main_socket.CloseSocket();
    server_skeleton_ptr->StopOfferService();
}
void *pthread1(void *v_var)
{
    server_main_socket_DG.OpenSocket(SERVER_PORT);
    server_main_socket_DG.BindServer();
    cout << "shared " << server_skeleton_ptr << endl;
    while (1)
        Handle_IO();
}

void Handle_IO()
{
    sockaddr_in echoClntAddr;                    /* Address of datagram source */
    unsigned int clntLen = sizeof(echoClntAddr); /* Address length */
    ara::com::proxy_skeleton::event_info evr;
    std::vector<uint8_t> msg;
    uint32_t msg_size;

    server_main_socket_DG.UDPRecFrom((void *)&msg_size, sizeof(msg_size), (struct sockaddr *)&echoClntAddr, &clntLen);
    msg.resize(msg_size);
    server_main_socket_DG.UDPRecFrom((void *)&msg[0], msg_size, (struct sockaddr *)&echoClntAddr, &clntLen);

    // ara::com::proxy_skeleton::Client_udp_Info cudp;
    // cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
    if (msg[14] == 0x02)
    {
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;

        sd_msg.Deserialize(msg);
        auto entry = (ara::com::entry::EventgroupEntry *)sd_msg.Entries()[0];

        ara::com::proxy_skeleton::Client_udp_Info cudp;
        cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
        printf("\n[SERVER]  ->> Handling client %s   with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), msg_size);
        switch (entry->Type())
        {
        case ara::com::entry::EntryType::Subscribing:
            switch (entry->ServiceId())
            {
            case SERVICE_ID:
                switch (entry->EventgroupId())
                {
                // case 0:
                //     std::cout << "[server] sub event1 start\n";
                //     server_skeleton_ptr->event1.subhandlecall(sd_msg, cudp);
                //     // stop = false; // for debuging
                //     break;
                // case 1:
                //     std::cout << "[server] sub event2 start\n";
                //     server_skeleton_ptr->event2.subhandlecall(sd_msg, cudp);
                //     break;
                case 0:
                    std::cout << "[server] sub field1 start\n";
                    server_skeleton_ptr->CurrentStatus.subhandlecall(sd_msg, cudp);
                    break;

                default: // error invalid eventgroup id
                    break;
                }
                break;
            }
        default: // reply with error invalid servic id
            break;
        }
    }
    // if (evr.data_size)
    // {
    //     if (evr.operation == 1)
    //     {
    //         server_main_socket_DG.UDPRecFrom((void *)&cudp.port, evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
    //     }
    //     else
    //     {
    //         server_main_socket_DG.UDPRecFrom((void *)&msg[0], evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
    //         std::cout << "got value of set\n";
    //     }
    // }
    // printf("\n[SERVER]  ->> Handling client %s %d  with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), cudp.port, evr.data_size);
}

