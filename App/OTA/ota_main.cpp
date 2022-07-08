/**
 * @file ota_main.cpp
 * @author 
 * @brief ota proccess main function
 ********************************************************************************/

#include <iostream>
#include <string>
#include <unistd.h>
#include "OTA/meta_data_storage.hpp"
#include "OTA/client.hpp"


// ara::com related includes
#include "ara/ucm/pkgmgr/ucm_return_types.hpp"
#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include "ara/ucm/pkgmgr/packagemanagement_proxy.hpp"
#include "ara/exec/execution_client.hpp"
#include "ara/sm/triggerin/triggerin_proxy.hpp"


//// Defines
#define META_DATA_FILE_PATH "./meta-data.dat"
#define FREQUENCY 10        // 10 seconds


// ara::com related defines
#define SD_PORT                         1690
#define PKG_SERVICE_ID                  45
#define SM_OTA_TRIGGERIN_SERVICE_ID     56
#define UDP_PORT_EVENTS                 7575
#define NUM_THREADS                     3

//// Namespaces
using namespace OTA;
using namespace ara::exec;

//// Functions declarations
void  handle_sigterm(int sig);  
void *pthread0(void *v_var);
void *pthread1(void *v_var);


//// Globale variables
CServer ssevent(SOCK_DGRAM);

/** pakage management proxy **/
ara::com::FindServiceHandle findhandle{PKG_SERVICE_ID, 0, SD_PORT};
std::shared_ptr<ara::ucm::pkgmgr::proxy::PackageManagementProxy> server_proxy_ptr;
/** OTA Trigger in Proxy    **/
ara::com::FindServiceHandle findhandle_ota_triggerin{SM_OTA_TRIGGERIN_SERVICE_ID, 0, SD_PORT};
std::shared_ptr<ara::sm::triggerin::proxy::Trigger_In_OTA_Proxy> server_proxy_ota_triggerin_ptr;

ara::sm::triggerin::OTA_State ota_state_g = ara::sm::triggerin::OTA_State::OTA_STATE_UNKNOWN;


ExecutionClient client;                                 // create execution client
int sigval = 0;

int main(void) {
    signal(SIGTERM, handle_sigterm);                        // register signal handler
    cout<<"\t\t[OTA]creating execution client "<<endl;
    client.ReportExecutionState(ExecutionState::kRunning);  // report execution state to the execution server

    ssevent.OpenSocket(UDP_PORT_EVENTS);
    ssevent.BindServer();

    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand = (ara::ucm::pkgmgr::proxy::PackageManagementProxy::FindService(findhandle)[0]);
    hand.UDP_port = UDP_PORT_EVENTS;
    server_proxy_ptr = std::make_shared<ara::ucm::pkgmgr::proxy::PackageManagementProxy>(hand);
    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle hand_OTA = ara::sm::triggerin::proxy::Trigger_In_OTA_Proxy::FindService(findhandle_ota_triggerin)[0];
    hand_OTA.UDP_port = UDP_PORT_EVENTS;
    server_proxy_ota_triggerin_ptr = std::make_shared<ara::sm::triggerin::proxy::Trigger_In_OTA_Proxy>(hand_OTA);

    cout<<"[OTA] Starting OTA process"<<endl;
    std::cout << "handle : " << hand.m_server_com.port_number << " " << hand.m_server_com.service_id << std::endl;
    std::cout << "handle : " << hand_OTA.m_server_com.port_number << " " << hand_OTA.m_server_com.service_id << std::endl;
    std::cout << "\t\t\t[CLIENT] starting\n";
    ota_state_g = ara::sm::triggerin::OTA_State::OTA_STATE_INITIALIZED;
    server_proxy_ota_triggerin_ptr->trigger.Set(ota_state_g);


    /* thread */
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

/////// Functions definitions
/**
 * @brief Signal handler for SIGTERM
 * @param sig signal number
 * @return void
 */
void handle_sigterm(int sig){
    sigval = 1;                                 // set signal value will be used as flag
    cout<<"{SM} terminating"<<endl;            
    // TODO: send termination to EM   


    exit(0);
}


void *pthread0(void *v_var) {

    std::cout << std::endl << "[OTA] started ..." << std::endl;

    while(true)
    {
        // creating the cloud client and connecting to the server
        std::cout << "[OTA] connecting to the cloud server ..." << std::endl;
        Client cloud;
        

        if( cloud.cloudConnect(OTA_IP_CLOUD, OTA_PORT_CLOUD) )
        {

            std::cout << "\t[OTA] connection succeeded ..." << std::endl;

            // requesting the new metaData from the cloud server
            std::string  json;
            cloud.requestMetadata(json);
            
            MetaData new_metaData(json);
            
            // retrieve the old meta-data stored in the file 
            MetaDataStorage fileSystem(META_DATA_FILE_PATH);
            std::vector<MetaData> metaDataList = fileSystem.load_MetaData();
            std::size_t listSize = metaDataList.size();
            MetaData old_metaData;

            if(metaDataList.size() != 0) {
                
                // getting the meta data of the same applicaton 
                for(std::size_t i = (listSize - 1); i  >= 0; i--)
                {
                    if(new_metaData == metaDataList[i])
                    {
                        old_metaData = metaDataList[i];
                        break;
                    }
                }
            }

            // comparing the application meta-data with old one stored in the file system
            if(new_metaData.get_version() > old_metaData.get_version()){
                
                std::cout << "\t[OTA] downloading the new package ..." << std::endl;
                
                // downloading the package from the cloud
                std::vector<uint8_t> package;
                cloud.requestPackage(package, signature);

                std::cout << "\t[OTA] sending the package to the flashing adapter ..." << std::endl;

                /** start sending the package to the ucm **/

                std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> result; /* Saves TransferStartOutput */
                std::vector<uint8_t> small_data;
                
                uint64_t package_size = package.size();
                result = server_proxy_ptr->TransferStart(package_size);
                ara::ucm::pkgmgr::PackageManagement::TransferStartOutput transfer_start_output = result.get();

                int block_counter = 0;
                for (int i=0; i<package.size(); i++)
                {
                    for(int j=0; j<transfer_start_output.BlockSize; j++)
                    {
                        if(i*transfer_start_output.BlockSize+ j >= package.size()){
                            small_data.resize(transfer_start_output.BlockSize);
                            break;
                        }
                        else
                            small_data.push_back(package[i*transfer_start_output.BlockSize + j]);
                    }

                    // don't change 64 (packagemanagementskeleton.cpp)
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> result2 =
                    server_proxy_ptr->TransferData(transfer_start_output.id, small_data, block_counter);   /* Saves TransferDataOutput */

                    ara::ucm::pkgmgr::PackageManagement::TransferDataOutput result3;
                    result3 =result2.get();
                    block_counter++;
                    small_data.clear();
                    if(block_counter*transfer_start_output.BlockSize > package.size()) break;
                }
                server_proxy_ptr->TransferExit(transfer_start_output.id);
                
                /** end of sending the package to the ucm **/

                /* process sw package */
                server_proxy_ptr->ProcessSwPackage(transfer_start_output.id);


                bool acknowlege = true; // this acknowle


                if(acknowlege)
                {
                    // updating the stored meta-data
                    std::cout << "\t[OTA] updating the stored meta-data ..." << std::endl;
                    fileSystem.save_MetaData(new_metaData);
                }
                else
                {
                    // the package failed to be fetched
                    std::cout << "\t[OTA] (rollback) package failed to be flashed ..." << std::endl;

                }

            }
            else {
                std::cout << "\t[OTA] no new versions in the cloud ..." << std::endl;
            }

            // disconnecting from the cloud connection
            cloud.cloudDisconnect();

        }
        else {
            std::cout << "\t[OTA] connection failed..." << std::endl;
        }

        sleep(FREQUENCY);

    } // end of while(true)

}

void *pthread1(void *v_var)
{
    while (1)
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

        if(Nmsg.MessageId().serivce_id == server_proxy_ptr->CurrentStatus.Get_event_id()){ //lkd wgdnaha
            if(Nmsg.MessageId().method_id & 0x7FFF == 0){
                server_proxy_ptr->CurrentStatus.handlecall(msg);
                std::cout << "NEW EVENT1 : " << server_proxy_ptr->CurrentStatus.get_value() << std::endl;
            }
            else{
                ///@todo Send Error Message unknown event_id
            }
        }
        else{
            ///@todo Send Error Message unknown service_id
        }

        // switch (Nmsg.MessageId().serivce_id)
        // {
        // case PKG_SERVICE_ID:
        //     switch (Nmsg.MessageId().method_id & 0x7FFF)
        //     {
        //     case 0:
        //         server_proxy_ptr->CurrentStatus.handlecall(msg);
        //         std::cout << "NEW EVENT1 : " << server_proxy_ptr->CurrentStatus.get_value() << std::endl;
        //         break;
        //     default:
        //         break;
        //     }
        //     break;

        // default:
        //     break;
        // }
    }
}

