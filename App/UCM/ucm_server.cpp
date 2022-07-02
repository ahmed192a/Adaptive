/// Includes
#include <iostream>
#include <string.h>
#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/SOMEIP/Message.hpp"
#include "ara/sm/triggerin/triggerin_proxy.hpp"
#include "ara/sm/triggerin/triggerin_types.hpp"
#include "ara/exec/execution_client.hpp"

/// Defines
#define SERVER_PORT         5365
#define SD_PORT             1690
#define MAX_QUEUE_CLIENTS   5
#define INSTANCE_ID          45
#define NUM_THREADS         3
#define SM_TRIGGERIN_SERVICE_ID 55

/// Namespaces
using namespace std;
using namespace ara::exec;

/// Functions declarations
void *pthread0(void *v_var);
void *pthread1(void *v_var);
void  handle_sigterm(int sig);


/// Globale variables
int sigval = 0;

ara::com::InstanceIdentifier instance(INSTANCE_ID);
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle{SERVER_PORT, SD_PORT};
std::shared_ptr<ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton> server_skeleton_ptr = std::make_shared<ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton>(instance, skeleton_handle);
// Socket for events
CServer server_main_socket_DG(SOCK_DGRAM);
// main server TCP socket for methods handle
CServer server_main_socket(SOCK_STREAM); 
ara::com::FindServiceHandle findhandle{SM_TRIGGERIN_SERVICE_ID, 0, SD_PORT};
ara::sm::triggerin::UCM_State ucm_state_g = ara::sm::triggerin::UCM_State::UCM_STATE_UNKNOWN;
std::shared_ptr<ara::sm::triggerin::proxy::Trigger_In_UCM_Proxy> triggerin_proxy_ptr;

int main()
{
    signal(SIGTERM, handle_sigterm);
    cout<<"\t\t[UCM]creating execution client "<<endl;
    ExecutionClient client;
    client.ReportExecutionState(ExecutionState::kRunning);



    // UDP Server sockets for events
    server_main_socket_DG.OpenSocket(SERVER_PORT);
    server_main_socket_DG.BindServer();
    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand = (ara::sm::triggerin::proxy::Trigger_In_UCM_Proxy::FindService(findhandle)[0]);
    hand.UDP_port = SERVER_PORT;
    triggerin_proxy_ptr = std::make_shared<ara::sm::triggerin::proxy::Trigger_In_UCM_Proxy>(hand);


    pthread_t threads[NUM_THREADS];

    int th1, th2;
    int i = 0;

    th1 = pthread_create(&threads[0], NULL, pthread0, (void *)&i);
    if (th1)
    {
        cout << "[UCM SERVER] ERROR can't create thread " << th1 << endl;
        exit(-1);
    }
    i = 1;
    th2 = pthread_create(&threads[1], NULL, pthread1, (void *)&i);
    if (th2)
    {
        cout << "[UCM SERVER] ERROR can't create thread " << th2 << endl;
        exit(-1);
    }

    pthread_exit(NULL);

    return 0;
}

void handle_sigterm(int sig){
    sigval = 1;
    cout<<"{UCM} terminating"<<endl;
    // send termination to EM
    server_skeleton_ptr->StopOfferService();    // stop offering service
    server_main_socket.CloseSocket();           // close server socket
    server_main_socket_DG.CloseSocket();        // close server socket

    exit(0);
}

void *pthread0(void *v_var)
{
    // TCP with client 
    cout<<"[UCM SERVER] OPEN SOCKET ON "<<endl;
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    cout<<"[UCM SERVER] OFFER SERVER "<<endl;
    server_skeleton_ptr->OfferService();
    ucm_state_g = ara::sm::triggerin::UCM_State::UCM_STATE_INITIALIZED; // set ucm state to initialized
    triggerin_proxy_ptr->trigger.Set(ucm_state_g);  // set triggerin proxy state to initialized to inform SM

    cout << "\t[SERVER]  Ready" << endl;

    while (1)
    {
        Socket Sclient = server_main_socket.AcceptServer();
        cout << "\t[SERVER]  accepted" << endl;

        // Payload message from client
        std::vector<uint8_t> msg;  
        // Size of message                         
        uint32_t msg_size;

        // Receive a payload from client containing the method name and parameters
        Sclient.Receive((void *)&msg_size, sizeof(msg_size));   // recieve message size 
        msg.resize(msg_size);           //  resize the vector to allocate size of the coming message
        Sclient.Receive((void *)&msg[0], msg_size);             //  recieve the message


        cout << "\t[SERVER]  received" << endl;
        ara::com::SOMEIP_MESSAGE::Message someip_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg);

        
        if (someip_msg.check_Methode_ID() == true)
        {
            cout << "This is method request " << endl;
            // hendling method request
            server_skeleton_ptr->method_dispatch(someip_msg, Sclient);
        }
        else
        {
            cout << "This is SET OR GET request" << endl;
            // handling GET or SET field request
            server_skeleton_ptr->field_method_dispatch(someip_msg, Sclient);
        }
        cout<< "finish request \n";

    }
    server_skeleton_ptr->StopOfferService();    // stop offering service
    server_main_socket.CloseSocket();           // close server socket
}
void *pthread1(void *v_var)
{
    while (1)
    {
        sockaddr_in echoClntAddr;                       // Address of datagram source 
        unsigned int clntLen = sizeof(echoClntAddr);    // Address length 
        std::vector<uint8_t> msg;                       // Payload message from client
        uint32_t msg_size;                              // Size of message

        server_main_socket_DG.UDPRecFrom((void *)&msg_size, sizeof(msg_size), (struct sockaddr *)&echoClntAddr, &clntLen);
        msg.resize(msg_size);
        server_main_socket_DG.UDPRecFrom((void *)&msg[0], msg_size, (struct sockaddr *)&echoClntAddr, &clntLen);


        if (msg[14] == 0x02) // make sure it's SOMEIP/SD message
        {
            ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
            ara::com::proxy_skeleton::Client_udp_Info cudp;


            sd_msg.Deserialize(msg);
            auto entry = (ara::com::entry::EventgroupEntry *)sd_msg.Entries()[0];

            cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));

            printf("\n[SERVER]  ->> Handling client %s   with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), msg_size);

            switch (entry->ServiceId())
            {
            case INSTANCE_ID:
                switch (entry->EventgroupId())
                {
                case 0:
                    std::cout << "[server] sub field1 start\n";
                    server_skeleton_ptr->CurrentStatus.subhandlecall(sd_msg, cudp);
                    break;

                default: // error invalid eventgroup id
                    break;
                }
                break;
            default:    // reply with error invalid service id
            break;

            }

        }
    }
}


