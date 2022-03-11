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
using event_info = ara::com::proxy_skeleton::event_info;

CServer server_main_socket(SOCK_STREAM); // Socket between the server and the client
skeleton server_skeleton_obj(SERVICE_ID);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);

void subscribe_handler2(int signum, siginfo_t *siginfo, void *ucontext);

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
    ara::com::proxy_skeleton::skeleton::EVENT::set_handle(&subscribe_handler2);

    // send to service discovery the offered service
    server_skeleton_obj.start_service();

    /* TCP with client */
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    Socket Sclient =  server_main_socket.AcceptServer();
    cout << blue << "\t[SERVER]  accepted" << endl;

    strcpy(buffer, "=> Server connected...\n");

    // send a confirmation connect to client
    Sclient.Send(buffer, strlen(buffer));

    // Receive a struct from client containing the method name and parameters
    Sclient.Receive((void *)&msg_size, sizeof(msg_size));
    msg.resize(msg_size);
    Sclient.Receive((void *)&msg[0], sizeof(msg));

    Sclient.Receive((void *)&x, sizeof(x));

    // print the requested method
    cout << blue << "\t[SERVER] " << x.method_name << endl;

    // Perform the requested method then send the result
    server_skeleton_obj.method_dispatch(msg, Sclient);

    /////////////////////////////////////////////////////////////////////////////////////
    while (server_skeleton_obj.event1.subscribers_data.empty())
    {
    }
    std::cout << blue << "\t[SERVER] : ";
    server_skeleton_obj.event1.update(7);

    sleep(1);
    while (server_skeleton_obj.event2.subscribers_data.empty())
    {
    }
    std::cout << blue << "\t[SERVER] : ";

    server_skeleton_obj.event2.update(9);

    int y = 2;
    while (server_skeleton_obj.field1.subscribers_data.empty())
    {
    }

    std::cout << blue << "\t[SERVER] : ";
    server_skeleton_obj.field1.update(y);

    while (!server_skeleton_obj.field1.subscribers_data.empty()) // test uns
    {
    }

    cout << blue << "\n\t[SERVER] Goodbye..." << endl;

    server_skeleton_obj.StopOfferService();

    // always be awake to receive stuff from signal
    while (1)
        sleep(100);
    server_main_socket.CloseSocket();
    return 0;
}

void subscribe_handler2(int signum, siginfo_t *siginfo, void *ucontext)
{
    // the next line isn't good but we use it her just for testing for now
    Socket soc = server_main_socket.AcceptServer();
    event_info R_e_info;

    if (signum != SIGUSR1)
        return;
    if (siginfo->si_code != SI_QUEUE)
        return;

    cout << blue << "\t[SERVER] receiver: Got value " << siginfo->si_int << endl;

    switch (siginfo->si_int)
    {
    case 2:
        //soc =  server_main_socket.AcceptServer();
        soc.Receive((void *)&R_e_info, sizeof(R_e_info));
        std::cout << "service id " << R_e_info.service_id << " eve id " << R_e_info.event_id << std::endl;

        switch (R_e_info.service_id)
        {
        case 32:

            switch (R_e_info.event_id)
            {
            case 0:
                server_skeleton_obj.event1.set_subscriber(R_e_info.process_id);
                std::cout << blue << "\n\t[SERVER] Event1: ";
                server_skeleton_obj.event1.print_subscribers();
                break;
            case 1:
                server_skeleton_obj.event2.set_subscriber(R_e_info.process_id);
                std::cout << blue << "\n\t[SERVER] Event2: ";
                server_skeleton_obj.event2.print_subscribers();
                break;
            case 2:
                server_skeleton_obj.field1.set_subscriber(R_e_info.process_id);
                std::cout << blue << "\n\t[SERVER] Field1: ";
                server_skeleton_obj.field1.print_subscribers();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        soc.CloseSocket();
        break;
    case 3:
        //soc =  server_main_socket.AcceptServer();
        soc.Receive((void *)&R_e_info, sizeof(R_e_info));
        std::cout << "service id " << R_e_info.service_id << " eve id " << R_e_info.event_id << std::endl;

        switch (R_e_info.service_id)
        {
        case 32:

            switch (R_e_info.event_id)
            {
            case 0:
                server_skeleton_obj.event1.Del_subscriber(R_e_info.process_id);
                std::cout << blue << "\n\t[SERVER] Event1: ";
                server_skeleton_obj.event1.print_subscribers();
                break;
            case 1:
                server_skeleton_obj.event2.Del_subscriber(R_e_info.process_id);
                std::cout << blue << "\n\t[SERVER] Event2: ";
                server_skeleton_obj.event2.print_subscribers();
                break;
            case 2:
                server_skeleton_obj.field1.Del_subscriber(R_e_info.process_id);
                std::cout << blue << "\n\t[SERVER] Field1: ";
                server_skeleton_obj.field1.print_subscribers();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        soc.CloseSocket();
        break;
    case 4:
        //soc = server_main_socket.AcceptServer();
        soc.Receive((void *)&R_e_info, sizeof(R_e_info));
        std::cout << "service id " << R_e_info.service_id << " eve id " << R_e_info.event_id << std::endl;

        switch (R_e_info.service_id)
        {
        case 32:

            switch (R_e_info.event_id)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                soc.Send((void *)&server_skeleton_obj.field1.event_data, sizeof(server_skeleton_obj.field1.event_data));

                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        soc.CloseSocket();

        break;
    case 5:
        //soc = server_main_socket.AcceptServer();
        soc.Receive((void *)&R_e_info, sizeof(R_e_info));
        std::cout << "service id " << R_e_info.service_id << " eve id " << R_e_info.event_id << std::endl;

        switch (R_e_info.service_id)
        {
        case 32:

            switch (R_e_info.event_id)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                soc.Receive((void *)&server_skeleton_obj.field1.event_data, sizeof(server_skeleton_obj.field1.event_data));

                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        soc.CloseSocket();

        break;
    default:
        break;
    }
}