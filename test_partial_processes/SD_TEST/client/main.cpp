#include <signal.h>
#include "ara/SD_c/proxy.hpp"
#include <iostream>
#include "color/color.hpp"
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"

#define SD_PORT 1690
#define SERVICE_ID 32
#define NUM_THREADS 3
#define UDP_PORT_EVENTS  7575


using namespace std;

CServer ssevent(SOCK_DGRAM);
ara::com::FindServiceHandle findhandle{SERVICE_ID, 32, SD_PORT};
// ara::com::FindServiceHandle findhandle1{47, 47, SD_PORT};

std::shared_ptr<saam::proxy> server_proxy_ptr ;
// std::shared_ptr<saam::proxy> server_proxy_ptr1 ;

// static CClient *client_event_ptr;
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);


void Event_Handler();

void *pthread0(void *v_var);
void *pthread1(void *v_var);

int main(int argc, char **argv)
{
    ssevent.OpenSocket(UDP_PORT_EVENTS);
    ssevent.BindServer();


    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand = (saam::proxy::FindService(findhandle)[0]);
    hand.UDP_port=UDP_PORT_EVENTS;
    server_proxy_ptr = std::make_shared<saam::proxy>(hand);


    // ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand1 = (saam::proxy::FindService(findhandle1)[0]);
    // hand1.UDP_port = UDP_PORT_EVENTS;
    // server_proxy_ptr1 = std::make_shared<saam::proxy>(hand1);



    std::cout << "handle : " << hand.m_server_com.port_number << " " << hand.m_server_com.service_id << std::endl;

    std::cout << "\t\t\t[CLIENT] starting\n";
    sleep(2);
    std::cout << "\t\t\t[CLIENT] starting\n";

    /*thread*/
    pthread_t threads[NUM_THREADS];

    int th1, th2;
    int i = 0;

    th1 = pthread_create(&threads[0], NULL, pthread0, (void *)&i);
    if (th1)
    {
        cout << "ERROR" << th1 << endl;
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
/*******************************************************************************************************************
 * @brief 
 * 
 * @param v_var 
 * @return void* 
 */
void *pthread0(void *v_var)
{
    std::string sma = "heloo";
    std::cout << green;
    pid_t pid = getpid();
    std::cout << "\t\t\t[CLIENT] receiver: PID is " << pid << std::endl;
    int result;

    // std::cout << "\t\t\t[CLIENT] Result of ADD : ";
    // result = server_proxy_ptr->ADD(7, 85);
    // std::cout << result << std::endl;
    // sleep(3);
    server_proxy_ptr->ev1.Subscribe();

    // sleep(3);
    // server_proxy_ptr->ev2.Subscribe();
    // sleep(3);
    // server_proxy_ptr->fd1.Subscribe();
    // sleep(3);
    // int x = 565;
    // std::cout << "\n\t\t\t[CLIENT] set field1 = " << server_proxy_ptr->fd1.Set(x) << std::endl;
    // sleep(2);
    // std::cout << "\n\t\t\t[CLIENT] get field1 = " << server_proxy_ptr->fd1.Get() << std::endl;
    // sleep(2);
    // server_proxy_ptr->fd1.UnSubscribe();

    // std::cout << "\t\t\t[CLIENT] Result of ADD : ";
    // result = server_proxy_ptr1->ADD(7, 4);
    // std::cout << result << std::endl;


    while (1)
    {
        sleep(1);
        printf(".\n");
        fflush(stdout);
    }
}
/**********************************************************************************************************************
 * @brief handle all event and field updates
 *
 * @param sigtype
 */
void *pthread1(void *v_var)
{
    // while (1)
    //     Event_Handler();

}
void Event_Handler()
{
    sockaddr_in echoClntAddr;                    /* Address of datagram source */
    unsigned int clntLen = sizeof(echoClntAddr); /* Address length */

    ara::com::proxy_skeleton::event_info evr;
    std::vector<uint8_t> msg;

    ssevent.UDPRecFrom((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr, &clntLen);
    printf("\t[CLIENT]  ->> Handling client %s %d\n", inet_ntoa(echoClntAddr.sin_addr), echoClntAddr.sin_port);
    fflush(stdout);
    msg.resize(evr.data_size);
    if (evr.data_size)
    {
        ssevent.UDPRecFrom((void *)&msg[0], msg.size(), (struct sockaddr *)&echoClntAddr, &clntLen);
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
