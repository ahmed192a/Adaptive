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
#define MAX_QUEUE_CLIENTS 1

struct event_info
{
    int process_id;
    char event_name[30];
};

using namespace std;
using C_Info = ara::com::proxy_skeleton::C_Info;
// extern void (*g_handler)(int, siginfo_t *, void *);

CServer server_main_socket(SOCK_STREAM); // Socket between the server and the client
std::shared_ptr<ara::com::proxy_skeleton::skeleton::Event<int>> event1;
std::shared_ptr<ara::com::proxy_skeleton::skeleton::Event<int>> event2;
std::shared_ptr<ara::com::proxy_skeleton::skeleton::Field<int>> field1;
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);
/**
 * @todo
 *  - add event , field in skeleton
 *  - GET, SET in field
 */
void subscribe_handler2(int signum, siginfo_t *siginfo, void *ucontext);

int main(int argc, char **argv)
{
    /// VARIABLES
    char buffer[256];
    C_Info x;
    skeleton server_skeleton_obj(32);
    std::vector<uint8_t> msg;
    int msg_size;
    ara::com::Deserializer dser;

    // We take the sever port number as the first argument
    cout << blue << "\t[SERVER] mypid: " << getpid() <<   endl;

    // g_handler = &subscribe_handler2;
    ara::com::proxy_skeleton::skeleton::EVENT::set_handle(&subscribe_handler2);

    event1 = std::make_shared<ara::com::proxy_skeleton::skeleton::Event<int>>(&server_skeleton_obj, "event1");
    event2 = std::make_shared<ara::com::proxy_skeleton::skeleton::Event<int>>(&server_skeleton_obj, "event2");
    field1 = std::make_shared<ara::com::proxy_skeleton::skeleton::Field<int>>(&server_skeleton_obj, "field1");

    // send to service discovery the offered service
    server_skeleton_obj.start_service();

    /* TCP with client */
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    server_main_socket.AcceptServer();
    cout << blue << "\t[SERVER]  accepted" <<   endl;

    strcpy(buffer, "=> Server connected...\n");

    // send a confirmation connect to client
    server_main_socket.SendServer(buffer, strlen(buffer));

    // Receive a struct from client containing the method name and parameters
    server_main_socket.ReceiveServer((void *)&msg_size, sizeof(msg_size));
    msg.resize(msg_size);
    server_main_socket.ReceiveServer((void *)&msg[0], sizeof(msg));

    server_main_socket.ReceiveServer((void *)&x, sizeof(x));

    // print the requested method
    cout << blue << "\t[SERVER] " << x.method_name <<   endl;

    // Perform the requested method then send the result
    server_skeleton_obj.method_dispatch(msg, server_main_socket);

    /////////////////////////////////////////////////////////////////////////////////////
    while (event1->subscribers_data.empty())
    {
    }
    event1->update(7);

    sleep(1);
    while (event2->subscribers_data.empty())
    {
    }
    event2->update(9);

    int y = 2;
    while (field1->subscribers_data.empty())
    {
    }
    // field1->update(y , x.process_id);
    field1->update(y);

    cout << blue << "\n\t[SERVER] Goodbye..." <<   endl;

    server_skeleton_obj.StopOfferService();

    // always be awake to receive stuff from signal
    while (1)
        sleep(100);
    server_main_socket.CloseSocket();
    return 0;
}

void subscribe_handler2(int signum, siginfo_t *siginfo, void *ucontext)
{
    static int count = 0;
    if (signum != SIGUSR1)
        return;
    if (siginfo->si_code != SI_QUEUE)
        return;

    cout << blue << "\t[SERVER] receiver: Got value " << siginfo->si_int <<   endl;

    if (siginfo->si_int == 2)
    {
        server_main_socket.AcceptServer();
        struct event_info e1;
        server_main_socket.ReceiveServer((struct event_info *)&e1, sizeof(struct event_info));

        std::cout << blue << "\t[SERVER]" << e1.event_name <<   endl;
        if (strcmp(e1.event_name, "event1") == 0)
        {
            event1->set_subscriber(e1.process_id);
            std::cout << blue << "\t[SERVER] Event1: " << std::endl;
            event1->print_subscribers();
        }
        else
        {
            event2->set_subscriber(e1.process_id);
            std::cout << blue << "\t[SERVER] Event2: " << std::endl;
            event2->print_subscribers();
        }

        count++;
    }
}