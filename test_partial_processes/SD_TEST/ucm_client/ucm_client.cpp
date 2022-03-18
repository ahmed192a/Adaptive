#include "iostream"
#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"

std::vector<char> ReadAllBytes(char const *filename)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);
    return result;
}


#include <signal.h>
#include "ara/ucm/pkgmgr/packagemanagement_proxy.hpp"
#include "ara/ucm/pkgmgr/ucm_return_types.hpp"

#include <iostream>
#include "color/color.hpp"
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>	
#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#define SD_PORT 1690
#define SERVICE_ID 45
#define UDP_PORT_EVENTS  7575

CClient client_event_h (SOCK_DGRAM);
CServer ssevent(SOCK_DGRAM);
ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handler;
ara::com::FindServiceHandle findhandle{SERVICE_ID, 45, SD_PORT};

//static ara::ucm::pkgmgr::proxy::PackageManagementProxy *server_proxy_ptr;
std::shared_ptr<ara::ucm::pkgmgr::proxy::PackageManagementProxy> server_proxy_ptr ;
// static CClient *client_event_ptr;
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

int main(int argc, char **argv)
{    
    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand = (ara::ucm::pkgmgr::proxy::PackageManagementProxy::FindService(findhandle)[0]);
    hand.UDP_port = UDP_PORT_EVENTS;
    server_proxy_ptr = std::make_shared<ara::ucm::pkgmgr::proxy::PackageManagementProxy>(hand);

    ssevent.OpenSocket(UDP_PORT_EVENTS);
    ssevent.BindServer();


    std::cout << "handle : " << hand.m_server_com.port_number << " " << hand.m_server_com.service_id << std::endl;

    std::cout << "\t\t\t[CLIENT] starting\n";
    sleep(2);
    client_event_h.OpenSocket();
    std::cout << "\t\t\t[CLIENT] starting\n";


    std::string sma = "heloo";
    std::cout << green;
    pid_t pid = getpid();
    std::cout << "\t\t\t[CLIENT] receiver: PID is " << pid << std::endl;
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> result; /* Saves TransferStartOutput */

    // Event
    // server_proxy_obj->FindService(32);

    std::cout << "\t\t\t[CLIENT] Result of TransferStart : ";
    std::vector<char> Temp_data = ReadAllBytes("../../../myfile.zip");
    std::vector<uint8_t> small_data;

    result = server_proxy_ptr->TransferStart(Temp_data.size());
    ara::ucm::pkgmgr::PackageManagement::TransferStartOutput transfer_start_output = result.get();

    int block_counter = 0;
     std::cout << Temp_data.size() << std::endl;
    for (int i=0; i<Temp_data.size(); i++)
    {
        for(int j=0; j<transfer_start_output.BlockSize; j++)
        {
            if(i*transfer_start_output.BlockSize+ j >= Temp_data.size()){
                small_data.resize(transfer_start_output.BlockSize);
                break;
            }
            else
                small_data.push_back(Temp_data[i*transfer_start_output.BlockSize + j]);
        }  
        
        // don't change 64 (packagemanagementskeleton.cpp)
        std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> result2 = 
        server_proxy_ptr->TransferData(transfer_start_output.id, small_data, block_counter);   /* Saves TransferDataOutput */

        ara::ucm::pkgmgr::PackageManagement::TransferDataOutput result3;
        result3 =result2.get();
        block_counter++;
        small_data.clear();
        if(block_counter*transfer_start_output.BlockSize > Temp_data.size()) break;
    }
    server_proxy_ptr->TransferExit(transfer_start_output.id);

    while (1)
    {
        sleep(1);
        printf(".\n");
        fflush(stdout);
    }
    

    return 0;
}


