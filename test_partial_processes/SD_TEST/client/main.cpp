#include <signal.h>
#include "ara/SD_c/proxy.hpp"
#include <iostream>
#include "color/color.hpp"
#include <arpa/inet.h>

#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#define SD_PORT 1690
#define SERVICE_ID 32
CServer client_event_h(SOCK_DGRAM);
saam::proxy server_proxy_obj(&client_event_h);
/**
 * @todo
 *  - event send data in update notify
 */
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);
void event_field_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
    if (signum != SIGUSR1)
        return;
    if (siginfo->si_code != SI_QUEUE)
        return;
    std::cout << "\t\t\t[CLIENT] receiver: Got value " << siginfo->si_int << std::endl;
}
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
void Event_Handler(int sigtype)
{


    sockaddr_in echoClntAddr; /* Address of datagram source */
    unsigned int clntLen;     /* Address length */

    ara::com::proxy_skeleton::event_notify<int> evr;
    clntLen = sizeof(echoClntAddr);
    client_event_h.UDPRecFrom((void *)&evr, sizeof(evr), (struct sockaddr *)&echoClntAddr, &clntLen);

    printf("\t[CLIENT]  ->> Handling client %s %d\n", inet_ntoa(echoClntAddr.sin_addr), echoClntAddr.sin_port);
    fflush(stdout);
    ara::com::proxy_skeleton::Client_udp_Info cudp;
    cudp.port = echoClntAddr.sin_port;
    cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
    switch (evr.service_id)
    {
    case SERVICE_ID:
        switch (evr.event_id)
        {
        case 0:
            server_proxy_obj.ev1.handlecall(evr);
            std::cout << "NEW EVENT1 : " << server_proxy_obj.ev1.get_value() << std::endl;
            break;
        case 1:
            server_proxy_obj.ev2.handlecall(evr);
            std::cout << "NEW EVENT2 : " << server_proxy_obj.ev2.get_value() << std::endl;

            break;
        case 2:
            server_proxy_obj.fd1.handlecall(evr);
            std::cout << "NEW FIELD1 : " << server_proxy_obj.fd1.get_value() << std::endl;

            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

int main(int argc, char **argv)
{
    client_event_h.OpenSocket(5875);
    client_event_h.BindServer();
    client_event_h.EnableInterrupt(Event_Handler);

    std::string sma = "heloo";
    std::cout << green;
    pid_t pid = getpid();
    std::cout << "\t\t\t[CLIENT] receiver: PID is " << pid << std::endl;
    int result;

    // struct sigaction signal_action;
    // signal_action.sa_sigaction = event_field_handler;
    // sigemptyset(&signal_action.sa_mask);
    // signal_action.sa_flags = SA_SIGINFO;
    // sigaction(SIGUSR1, &signal_action, NULL);

    // Event

    server_proxy_obj.FindService(32);

    std::cout << "\t\t\t[CLIENT] Result of ADD : ";
    result = server_proxy_obj.ADD(13, 85);
    std::cout << result << std::endl;

    server_proxy_obj.ev1.Subscribe();
    sleep(5);
    server_proxy_obj.ev2.Subscribe();
    sleep(5);
    server_proxy_obj.fd1.Subscribe();
    sleep(5);
    int x = 565;
    std::cout << "\n\t\t\t[CLIENT] set field1 = " << server_proxy_obj.fd1.Set(x) << std::endl;

    std::cout << "\n\t\t\t[CLIENT] get field1 = " << server_proxy_obj.fd1.Get() << std::endl;
    // sleep(5);

    server_proxy_obj.fd1.UnSubscribe();

    while (1)
    {
        sleep(1);
        printf(".\n");
        fflush(stdout);
    }

    return 0;
}