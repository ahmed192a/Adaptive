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

#define SERVER_PORT 5365
#define SD_PORT 1690
#define MAX_QUEUE_CLIENTS 5
#define SERVICE_ID 32

using namespace std;
void Handle_IO();

// Socket for methods
// Socket for events
CServer server_main_socket_DG(SOCK_DGRAM);

ara::com::InstanceIdentifier instance(SERVICE_ID);
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle{SERVER_PORT, SD_PORT};
skeleton server_skeleton_obj(instance, skeleton_handle);

static skeleton *server_skeleton_ptr;

int main()
{
    server_skeleton_ptr = (skeleton *)mmap(NULL, sizeof *server_skeleton_ptr, PROT_READ | PROT_WRITE,
                                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    memcpy(server_skeleton_ptr, &server_skeleton_obj, sizeof(server_skeleton_obj));

    int pid = fork();
    if (pid == 0)
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

        cout << "shared " << server_skeleton_ptr << endl;
        cout << "\t[SERVER]  Ready" << endl;
        Socket Sclient = server_main_socket.AcceptServer();
        cout << "\t[SERVER]  accepted" << endl;

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
        server_skeleton_ptr->method_dispatch(msg, Sclient);

        /////////////////////////////////////////////////////////////////////////////////////
        while (server_skeleton_ptr->event1.getsub().empty())
        {
        }
        std::cout << "\t[SERVER] : ";
        server_skeleton_ptr->event1.update(7);

        sleep(1);
        while (server_skeleton_ptr->event2.getsub().empty())
        {
        }
        std::cout << "\t[SERVER] : ";

        server_skeleton_ptr->event2.update(9);

        int y = 2;
        while (server_skeleton_ptr->field1.getsub().empty())
        {
        }

        std::cout << "\t[SERVER] : ";
        server_skeleton_ptr->field1.update(y);

        while (!server_skeleton_ptr->field1.getsub().empty()) // test uns
        {
        }

        cout << "\n\t[SERVER] Goodbye..." << endl;

        // always be awake to receive stuff from signal
        while (1)
        {
            printf(".\n");
            sleep(1);
        }

        server_main_socket.CloseSocket();
        server_skeleton_ptr->StopOfferService();
    }
    else
    {
        server_main_socket_DG.OpenSocket(SERVER_PORT);
        server_main_socket_DG.BindServer();
        cout << "shared " << server_skeleton_ptr << endl;
        while (1)
            Handle_IO();
    }

    return 0;
}

void Handle_IO()
{
    sockaddr_in echoClntAddr;                    /* Address of datagram source */
    unsigned int clntLen = sizeof(echoClntAddr); /* Address length */
    ara::com::proxy_skeleton::event_info evr;
    std::vector<uint8_t> msg;
    server_main_socket_DG.UDPRecFrom((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr, &clntLen);

    msg.resize(evr.data_size);
    ara::com::proxy_skeleton::Client_udp_Info cudp;
    cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
    if (evr.data_size)
    {
        if (evr.operation == 1)
        {
            server_main_socket_DG.UDPRecFrom((void *)&cudp.port, evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
        }
        else
        {
            server_main_socket_DG.UDPRecFrom((void *)&msg[0], evr.data_size, (struct sockaddr *)&echoClntAddr, &clntLen);
            std::cout << "got value of set\n";
        }
    }
    printf("\n[SERVER]  ->> Handling client %s %d  with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), cudp.port,  evr.data_size);

    switch (evr.service_id)
    {
    case SERVICE_ID:
        switch (evr.event_id)
        {
        case 0:
            std::cout << "[server] sub event1 start\n";
            server_skeleton_ptr->event1.handlecall(evr, msg, cudp);

            break;
        case 1:
            std::cout << "[server] sub event2 start\n";
            server_skeleton_ptr->event2.handlecall(evr, msg,cudp);

            break;
        case 2:
            server_skeleton_ptr->field1.handlecall(evr, msg, cudp);
            if (evr.operation == 4)
            {
                std::cout << "[server] get field1 " << std::endl;
                server_main_socket_DG.UDPSendTo((void *)&msg[0], msg.size(), (struct sockaddr *)&echoClntAddr);
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