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

#include <sys/mman.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <cstdlib>
#include <iostream>

#define SERVER_PORT         5365
#define SD_PORT             1690
#define MAX_QUEUE_CLIENTS   5
#define SERVICE_ID          32
#define NUM_THREADS         3

using namespace std;

// server 
CServer server_main_socket_DG(SOCK_DGRAM);

ara::com::InstanceIdentifier instance(SERVICE_ID);
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle{SERVER_PORT, SD_PORT};
std::shared_ptr<skeleton> server_skeleton_ptr = std::make_shared<skeleton>(instance, skeleton_handle);

bool stop =true;
// ara::com::InstanceIdentifier instance1(47);
// std::shared_ptr<skeleton> server_skeleton_ptr1 = std::make_shared<skeleton>(instance1, skeleton_handle);

void Handle_IO();
void *pthread0(void *v_var);
void *pthread1(void *v_var);

int main()
{
    pthread_t threads[NUM_THREADS];

    int th1 , th2;
    int i = 0;

        th1 = pthread_create(&threads[0] , NULL , pthread0 , (void *)&i);
        if(th1)
        {
            cout << "ERRor" << th1 << endl;
            exit(-1);

        }
        i = 1;
        th2 = pthread_create(&threads[1] , NULL , pthread1 , (void *)&i);
        if(th2)
        {
            cout << "ERRor" << th2 << endl;
            exit(-1);

        }
    
    pthread_exit(NULL);
    return 0;
}


/**************************************************** skeleton handle
 * @brief 
 * @todo send service id in the methods msg
 * 
 * @param v_var 
 * @return void* 
 */
void *pthread0(void *v_var)
{
    CServer server_main_socket(SOCK_STREAM);

    /// VARIABLES
    char buffer[256];
    C_Info x;
    std::vector<uint8_t> msg;
    int msg_size;
    ara::com::Deserializer dser;

    // We take the sever port number as the first argument
    cout << "\t[SERVER] mypid: " << getpid() << endl;
    /* TCP with client */
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    server_skeleton_ptr->OfferService();

    // server_skeleton_ptr1->OfferService();

    cout << "\t[SERVER]  Ready" << endl;
    Socket Sclient = server_main_socket.AcceptServer();
    cout << "\t[SERVER]  accepted" << endl;

    // strcpy(buffer, "=> Server connected...\n");

    // // // send a confirmation connect to client
    // Sclient.Send(buffer, strlen(buffer));

    // // Receive a struct from client containing the method name and parameters
    Sclient.Receive((void *)&msg_size, sizeof(msg_size));
    msg.resize(msg_size);
    Sclient.Receive((void *)&msg[0], sizeof(msg));
    ara::com::SOMEIP_MESSAGE::Message Request_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg);
    if(Request_msg.check_Methode_ID() == true)
    {
        cout<<"This is method request \n";
        server_skeleton_ptr->method_dispatch(Request_msg, Sclient);
    }else{
        // SET and GET REQUEST for fields
        cout<<"This is SET OR GET request \n";
        server_skeleton_ptr->field_method_dispatch(Request_msg, Sclient);
    }

 

    /////////////////////////////////////////////////////////////////////////////////////
    while (server_skeleton_ptr->event1.getsub().empty())
    {
        cout << "waiting for event1" << endl;
    }
    std::cout << "\t[SERVER] : ";
    server_skeleton_ptr->event1.update(7);

    // sleep(1);
    // while (server_skeleton_ptr->event2.getsub().empty())
    // {
    // }
    // std::cout << "\t[SERVER] : ";

    // server_skeleton_ptr->event2.update(9);

    // int y = 2;
    // while (server_skeleton_ptr->field1.getsub().empty())
    // {
    // }

    // std::cout << "\t[SERVER] : ";
    // server_skeleton_ptr->field1.update(y);

    // while (!server_skeleton_ptr->field1.getsub().empty()) // test uns
    // {
    // }

    // cout << "\n\t[SERVER] Goodbye..." << endl;

    // // always be awake to receive stuff from signal
    // while (1)
    // {
    //     printf(".\n");
    //     sleep(1);
    // }
    while(stop){
        printf(".\n");
        sleep(1);
    }

    server_main_socket.CloseSocket();
    server_skeleton_ptr->StopOfferService();
}


/******************************************************        Event handler    ************************************************
 * @brief 
 * 
 */

void *pthread1(void *v_var)
{
    server_main_socket_DG.OpenSocket(SERVER_PORT);
    server_main_socket_DG.BindServer();
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


    server_main_socket_DG.UDPRecFrom((void *)&msg_size, sizeof(msg_size),(struct sockaddr *)& echoClntAddr, &clntLen);
    msg.resize(msg_size);
    server_main_socket_DG.UDPRecFrom((void *)&msg[0], msg_size,(struct sockaddr *)& echoClntAddr, &clntLen);


    if(msg[14] = 0x02) // SD msg
    {
        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;

        sd_msg.Deserialize(msg);
        auto entry = (ara::com::entry::EventgroupEntry *)sd_msg.Entries()[0];

        ara::com::proxy_skeleton::Client_udp_Info cudp;
        cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
        printf("\n[SERVER]  ->> Handling client %s   with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), msg_size);
        switch(entry->Type()){
            case ara::com::entry::EntryType::Subscribing:
            switch(entry->ServiceId())
            {
                case SERVICE_ID:
                    switch (entry->EventgroupId())
                    {
                        case 0:
                            std::cout << "[server] sub event1 start\n";
                            server_skeleton_ptr->event1.subhandlecall(sd_msg, cudp);
                            // stop = false; // for debuging
                            break;
                        case 1:
                            std::cout << "[server] sub event2 start\n";
                            server_skeleton_ptr->event2.subhandlecall(sd_msg, cudp);
                            break;
                        case 2:
                            std::cout << "[server] sub field1 start\n";
                            server_skeleton_ptr->field1.subhandlecall(sd_msg, cudp);
                            break;

                        default: // error invalid eventgroup id
                            break;
                    }
                break;
            }
            default: // reply with error invalid servic id
            break;
        }
    }else{ // for get and set methods
          // handle get and set methods is dispatch method
    }


}
// void Handle_IO()
// {
//     sockaddr_in echoClntAddr;                    /* Address of datagram source */
//     unsigned int clntLen = sizeof(echoClntAddr); /* Address length */
//     ara::com::proxy_skeleton::event_info evr;
//     std::vector<uint8_t> msg;
//     server_main_socket_DG.UDPRecFrom((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr, &clntLen);

//     msg.resize(evr.data_size);
//     ara::com::proxy_skeleton::Client_udp_Info cudp;
//     cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
//     if (evr.data_size)
//     {
//         if (evr.operation == 1)
//         {
//             server_main_socket_DG.UDPRecFrom((void *)&cudp.port, evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
//         }
//         else
//         {
//             server_main_socket_DG.UDPRecFrom((void *)&msg[0], evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
//             std::cout << "got value of set\n";
//         }
//     }
//     printf("\n[SERVER]  ->> Handling client %s %d  with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), cudp.port, evr.data_size);

//     switch (evr.service_id)
//     {
//     case SERVICE_ID:
//         switch (evr.event_id)
//         {
//         case 0:
//             std::cout << "[server] sub event1 start\n";
//             server_skeleton_ptr->event1.handlecall(evr, msg, cudp);

//             break;
//         case 1:
//             std::cout << "[server] sub event2 start\n";
//             server_skeleton_ptr->event2.handlecall(evr, msg, cudp);

//             break;
//         case 2:
//             server_skeleton_ptr->field1.handlecall(evr, msg, cudp);
//             if (evr.operation == 4)
//             {
//                 std::cout << "[server] get field1 " << std::endl;
//                 server_main_socket_DG.UDPSendTo((void *)&msg[0], msg.size(), (struct sockaddr *)&echoClntAddr);
//             }
//             else if (evr.operation == 3)
//             {
//                 std::cout << "[server] set field1 " << std::endl;
//             }
//             else
//             {
//                 std::cout << "[server] sub field1 start\n";
//             }
//             break;

//         default:
//             break;
//         }
//         break;
//     default:
//         break;
//     }
// }