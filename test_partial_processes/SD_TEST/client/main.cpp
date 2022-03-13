#include <signal.h>
#include "ara/SD_c/proxy.hpp"
#include <iostream>
#include "color/color.hpp"
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>	/*  This file is necessary for using shared
			    memory constructs
			*/
#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#define SD_PORT 1690
#define SERVICE_ID 32
std::shared_ptr<CClient> client_event_h = std::make_shared<CClient>(SOCK_DGRAM);
ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handler;
ara::com::FindServiceHandle findhandle{SERVICE_ID, 32, SD_PORT};
static saam::proxy *server_proxy_ptr;

Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);

/**
 * @brief handle Event in client
 *
 *
 *
 * @todo
 *      - use serialzer and deserializer
 *      - get the second value which is event id then send it to the corresponding handler
 *
 * @param sigtype
 */
void Event_Handler();

int main(int argc, char **argv)
{    
    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand = (saam::proxy::FindService(findhandle)[0]);

    hand.m_client_UPD = &*client_event_h;

    saam::proxy server_proxy_obj(hand);
    server_proxy_ptr = (saam::proxy *)mmap(NULL, sizeof *server_proxy_ptr, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    memcpy(server_proxy_ptr, &server_proxy_obj, sizeof(server_proxy_obj));
    

    std::cout << "handle : " << hand.m_server_com.port_number << " " << hand.m_server_com.service_id << std::endl;

    std::cout << "\t\t\t[CLIENT] starting\n";
    sleep(2);
    client_event_h->OpenSocket();
    // client_event_h.BindServer();
    //  client_event_h->EnableInterrupt(Event_Handler);
    std::cout << "\t\t\t[CLIENT] starting\n";
    int pid = fork();
    if (pid == 0)
    {
        std::string sma = "heloo";
        std::cout << green;
        pid_t pid = getpid();
        std::cout << "\t\t\t[CLIENT] receiver: PID is " << pid << std::endl;
        int result;

        // Event
        // server_proxy_obj->FindService(32);

        std::cout << "\t\t\t[CLIENT] Result of ADD : ";
        result = server_proxy_ptr->ADD(13, 85);
        std::cout << result << std::endl;
        sleep(3);
        server_proxy_ptr->ev1.Subscribe();

        sleep(3);
        server_proxy_ptr->ev2.Subscribe();
        sleep(3);
        server_proxy_ptr->fd1.Subscribe();
        sleep(3);
        // int x = 565;
        // std::cout << "\n\t\t\t[CLIENT] set field1 = " << server_proxy_ptr->fd1.Set(x) << std::endl;
        // sleep(2);
        // std::cout << "\n\t\t\t[CLIENT] get field1 = " << server_proxy_ptr->fd1.Get() << std::endl;
        // sleep(2);
        // server_proxy_ptr->fd1.UnSubscribe();

        while (1)
        {
            sleep(1);
            printf(".\n");
            fflush(stdout);
        }
    }
    else
    {
        while (1)
            Event_Handler();
    }

    return 0;
}

/**
 * @brief handle all event and field updates
 *
 * @param sigtype
 */
void Event_Handler()
{
    // static uint8_t IO_Handler_count =0;

    // if(IO_Handler_count == 1)
    // {
    //     IO_Handler_count = 0;
    //     return;
    // }
    // IO_Handler_count++;
    sockaddr_in echoClntAddr;                    /* Address of datagram source */
    unsigned int clntLen = sizeof(echoClntAddr); /* Address length */

    ara::com::proxy_skeleton::event_info evr;
    std::vector<uint8_t> msg;

    client_event_h->UDPRecFrom((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr, &clntLen);
    printf("\t[CLIENT]  ->> Handling client %s %d\n", inet_ntoa(echoClntAddr.sin_addr), echoClntAddr.sin_port);
    fflush(stdout);
    msg.resize(evr.data_size);
    if (evr.data_size)
    {
        client_event_h->UDPRecFrom((void *)&msg[0], msg.size(), (struct sockaddr *)&echoClntAddr, &clntLen);
        // IO_Handler_count++;
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
            server_proxy_ptr->ev1.handlecall(evr, msg);
            std::cout << "NEW EVENT1 : " << server_proxy_ptr->ev1.get_value() << std::endl;
            break;
        case 1:
            server_proxy_ptr->ev2.handlecall(evr, msg);
            std::cout << "NEW EVENT2 : " << server_proxy_ptr->ev2.get_value() << std::endl;

            break;
        case 2:
            server_proxy_ptr->fd1.handlecall(evr, msg);
            std::cout << "NEW FIELD1 : " << server_proxy_ptr->fd1.get_value() << std::endl;

            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}
