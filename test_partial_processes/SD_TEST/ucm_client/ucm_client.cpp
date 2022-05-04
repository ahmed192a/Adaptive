#include "iostream"
#include "ara/ucm/pkgmgr/ucm_return_types.hpp"
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
#include "ara/ucm/pkgmgr/packagemanagement_proxy.hpp"

#define SD_PORT 1690
#define SERVICE_ID 45
#define UDP_PORT_EVENTS  7575
#define NUM_THREADS 3

using namespace std;

std::vector<char> ReadAllBytes(char const *filename)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);
    return result;
}
// /**
//  * @brief handle Event in client
//  *
//  *
//  *
//  * @todo
//  *      - use serialzer and deserializer
//  *      - get the second value which is event id then send it to the corresponding handler
//  *
//  * @param sigtype
//  */


// CClient client_event_h (SOCK_DGRAM);
// ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handler;

std::shared_ptr<ara::ucm::pkgmgr::proxy::PackageManagementProxy> server_proxy_ptr ;
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);



CServer ssevent(SOCK_DGRAM);
ara::com::FindServiceHandle findhandle{SERVICE_ID, 45, SD_PORT};



void Event_Handler();

void *pthread0(void *v_var);
void *pthread1(void *v_var);

int main(int argc, char **argv)
{
    ssevent.OpenSocket(UDP_PORT_EVENTS);
    ssevent.BindServer();

    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand = (ara::ucm::pkgmgr::proxy::PackageManagementProxy::FindService(findhandle)[0]);
    hand.UDP_port = UDP_PORT_EVENTS;
    server_proxy_ptr = std::make_shared<ara::ucm::pkgmgr::proxy::PackageManagementProxy>(hand);


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
    std::cout << green;
    pid_t pid = getpid();
    std::cout << "\t\t\t[CLIENT] receiver: PID is " << pid << std::endl;
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> result; /* Saves TransferStartOutput */

    std::cout << "\t\t\t[CLIENT] Result of TransferStart : ";
    std::vector<char> Temp_data = ReadAllBytes("../../../a.out");
    std::vector<uint8_t> small_data;

    result = server_proxy_ptr->TransferStart(Temp_data.size());
    ara::ucm::pkgmgr::PackageManagement::TransferStartOutput transfer_start_output = result.get();

    int block_counter = 0;
    std::cout << Temp_data.size() << std::endl;
    for (int i=0; i < Temp_data.size(); i += transfer_start_output.BlockSize)
    {
        for(int j=0; j<transfer_start_output.BlockSize; j++)
        {
            if(i + j >= Temp_data.size()){
                small_data.resize(transfer_start_output.BlockSize);
                break;
            }
            else
                small_data.push_back(Temp_data[i + j]);
        }

        // don't change 64 (packagemanagementskeleton.cpp)
        std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> result2 =
        server_proxy_ptr->TransferData(transfer_start_output.id, small_data, block_counter);   /* Saves TransferDataOutput */

        ara::ucm::pkgmgr::PackageManagement::TransferDataOutput result3;
        result3 =result2.get();   // get the value of future

        block_counter++;
        small_data.clear();
    }
    server_proxy_ptr->TransferExit(transfer_start_output.id);

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
    while (1)
        Event_Handler();
}
void Event_Handler()
{
    sockaddr_in echoClntAddr;                    /* Address of datagram source */
    unsigned int clntLen = sizeof(echoClntAddr); /* Address length */

     // ara::com::proxy_skeleton::event_info evr;
    std::vector<uint8_t> msg;
    uint32_t msg_size;

    ssevent.UDPRecFrom((void *)&msg_size, sizeof(msg_size), (struct sockaddr *)&echoClntAddr, &clntLen);
    msg.reserve(msg_size);
    ssevent.UDPRecFrom((void *)&msg[0], msg_size, (struct sockaddr *)&echoClntAddr, &clntLen);
    printf("\t[CLIENT]  ->> Handling client %s %d\n", inet_ntoa(echoClntAddr.sin_addr), echoClntAddr.sin_port);
    fflush(stdout);

    ara::com::proxy_skeleton::Client_udp_Info cudp;
    cudp.port = echoClntAddr.sin_port;
    cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));
    ara::com::SOMEIP_MESSAGE::Message Nmsg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg);
    msg = Nmsg.GetPayload();

    switch (Nmsg.MessageId().serivce_id)
    {
    case SERVICE_ID:
        switch (Nmsg.MessageId().method_id & 0x7FFF)
        {
        case 0:
            server_proxy_ptr->CurrentStatus.handlecall(msg);
            std::cout << "NEW EVENT1 : " << server_proxy_ptr->CurrentStatus.get_value() << std::endl;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}
