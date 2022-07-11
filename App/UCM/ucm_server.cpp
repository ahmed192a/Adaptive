/**
 * @file    ucm_server.cpp
 * @author  Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date
 *
 * @copyright Copyright (c) 2022
 *
 */
/************************************************************************
 * **********        INCLUDES         ***********************************
 * **********************************************************************/
#include <iostream>
#include <string.h>
#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/SOMEIP/Message.hpp"
#include "ara/sm/triggerin/triggerin_proxy.hpp"
#include "ara/sm/triggerin/triggerin_types.hpp"
#include "ara/exec/execution_client.hpp"

/************************************************************************
 *                           Defines                                    *
 ************************************************************************/
#define SERVER_PORT 5365           /*server port number*/
#define SD_PORT 1690               /*Service discovery port number*/
#define MAX_QUEUE_CLIENTS 5        /*Max number of clients*/
#define PKG_INSTANCE_ID 1          /*Instance Id*/
#define NUM_THREADS 3              /*number of threads*/
#define SM_TRIGGERIN_SERVICE_ID 55 /*SM_TRIGGERIN_SERVICE_ID in UCM skeleton*/

/// Namespaces
using namespace std;
using namespace ara::exec;

/************************************************************************
 * **********        Functions declarations      ************************
 * **********************************************************************/
void *pthread0(void *v_var); /*first thread*/
void *pthread1(void *v_var); /*second thread*/
void handle_sigterm(int sig);

/************************************************************************
 * **********        Globale variables      ************************
 * **********************************************************************/
int sigval = 0;

/**
 * @brief
 *
 * @return ara::com::InstanceIdentifier
 */
ara::com::InstanceIdentifier instance(PKG_INSTANCE_ID);
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle{SERVER_PORT, SD_PORT};

/*             Shared Pointer                       */
std::shared_ptr<ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton> server_skeleton_ptr = std::make_shared<ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton>(instance, skeleton_handle);
/*             Socket for events                    */
CServer server_main_socket_DG(SOCK_DGRAM);

/*       main server TCP socket for methods handle  */
CServer server_main_socket(SOCK_STREAM);

ara::com::FindServiceHandle findhandle{SM_TRIGGERIN_SERVICE_ID, 0, SD_PORT};
ara::sm::triggerin::UCM_State ucm_state_g = ara::sm::triggerin::UCM_State::UCM_STATE_UNKNOWN;
std::shared_ptr<ara::sm::triggerin::proxy::Trigger_In_UCM_Proxy> triggerin_proxy_ptr;
ExecutionClient client;

/**
 * @brief Main Function
 *
 * @return int
 */
int main()
{
    cout << "\t\t [UCM] Intialization ......" << endl;
    signal(SIGTERM, handle_sigterm);
    cout << "---------------------------------------------" << endl;
    cout << "\t\t[UCM]creating execution client " << endl;
    cout << "---------------------------------------------" << endl;
    client.ReportExecutionState(ExecutionState::kRunning);

    /*     UDP Server sockets for events      */
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
/**
 * @brief handle_sigterm -->
 *        stop offering service
 *        close server socket
 *        close server socket
 *
 * @param sig
 */
void handle_sigterm(int sig)
{
    sigval = 1;
    cout << "---------------------------------------------" << endl;
    cout << "[UCM] terminating" << endl;
    cout << "---------------------------------------------" << endl;
    client.ReportExecutionState(ExecutionState::kTerminating); // report execution state to the execution server

    // server_skeleton_ptr->StopOfferService();    /* stop offering service */
    server_main_socket.CloseSocket();    /* close server socket   */
    server_main_socket_DG.CloseSocket(); /* close server socket   */

    exit(0);
}

/**
 * @brief first thread to open socket
 *
 * @param v_var
 * @return void*
 */
void *pthread0(void *v_var)
{
    /* TCP with client */
    cout << "---------------------------------------------" << endl;
    cout << "[UCM SERVER] OPEN SOCKET ON " << endl;
    
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    cout << "[UCM SERVER] OFFER SERVER " << endl;
    server_skeleton_ptr->OfferService();
    ucm_state_g = ara::sm::triggerin::UCM_State::UCM_STATE_INITIALIZED; // set ucm state to initialized
    triggerin_proxy_ptr->trigger.Set(ucm_state_g);                      // set triggerin proxy state to initialized to inform SM

    cout << "---------------------------------------------" << endl;
    cout << "\t[SERVER]  Ready" << endl;
    cout << "---------------------------------------------" << endl;

    while (1)
    {
        Socket Sclient = server_main_socket.AcceptServer();
        cout << "---------------------------------------------" << endl;
        cout << "\t[SERVER]  accepted" << endl;
        cout << "---------------------------------------------" << endl;

        std::vector<uint8_t> msg; /* Payload message from client */
        uint32_t msg_size;        /* Size of message  */

        /*    Receive a payload from client containing the method name and parameters  */
        Sclient.Receive((void *)&msg_size, sizeof(msg_size)); /*  recieve message size   */
        msg.resize(msg_size);                                 /*  resize the vector to allocate size of the coming message  */
        Sclient.Receive((void *)&msg[0], msg_size);           /*  recieve the message  */
        
        cout << "---------------------------------------------" << endl;
        cout << "\t[SERVER]  received" << endl;
        cout << "---------------------------------------------" << endl;
        /*         SOMEIP_MESSAGE Deserialize    */
        ara::com::SOMEIP_MESSAGE::Message someip_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg);
        if (someip_msg.MessageId().serivce_id == server_skeleton_ptr->GetServiceId())
        {
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
        }
        else
        {
            cout << "[SERVER] received message from client but not from server" << endl;
            ara::com::proxy_skeleton::skeleton::ServiceSkeleton::NoServiceHandler(someip_msg, Sclient);
        }
        cout << "finish request \n";
    }
    server_skeleton_ptr->StopOfferService(); /* stop offering service  */
    server_main_socket.CloseSocket();        /* close server socket     */
}
/**
 * @brief second thread --> subscribe and unsubscribe for event
 *
 * @param v_var
 * @return void*
 */
void *pthread1(void *v_var)
{
    while (1)
    {
        sockaddr_in echoClntAddr;                    /* Address of datagram source  */
        unsigned int clntLen = sizeof(echoClntAddr); /* Address length */
        std::vector<uint8_t> msg;                    /* Payload message from client */
        uint32_t msg_size;                           /* Size of message  */

        server_main_socket_DG.UDPRecFrom((void *)&msg_size, sizeof(msg_size), (struct sockaddr *)&echoClntAddr, &clntLen);
        msg.resize(msg_size);
        server_main_socket_DG.UDPRecFrom((void *)&msg[0], msg_size, (struct sockaddr *)&echoClntAddr, &clntLen);

        if (msg[14] == 0x02) /* make sure it's SOMEIP/SD message */
        {
            ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
            ara::com::proxy_skeleton::Client_udp_Info cudp;

            sd_msg.Deserialize(msg);
            auto entry = (ara::com::entry::EventgroupEntry *)sd_msg.Entries()[0];

            cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));

            printf("\n[SERVER]  ->> Handling client %s   with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), msg_size);

            if (entry->ServiceId() == server_skeleton_ptr->GetServiceId())
            {
                if (entry->EventgroupId() == server_skeleton_ptr->CurrentStatus.Get_event_id())
                {
                    std::cout << "[server] sub field1 start\n";
                    server_skeleton_ptr->CurrentStatus.subhandlecall(sd_msg, cudp);
                }
                else
                {
                    ///@todo unknown eventgroup id
                }
            }
            else
            {
                cout << "[SERVER] received message from client but not from server" << endl;
                ///@todo unknown service id
            }
        }
    }
}
