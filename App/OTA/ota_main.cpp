/**
 * @file ota_main.cpp
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-07-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
#define FREQUENCY 10 // 10 seconds

// ara::com related defines
#define SD_PORT 1690
#define PKG_SERVICE_ID 45
#define SM_OTA_TRIGGERIN_SERVICE_ID 56
#define UDP_PORT_EVENTS 7575
#define NUM_THREADS 3

//// Namespaces
using namespace OTA;
using namespace ara::exec;

//// Functions declarations
void handle_sigterm(int sig);
void *pthread0(void *v_var);
void *pthread1(void *v_var);

//// Globale variables
CServer server_udp_socket(SOCK_DGRAM);

/** pakage management proxy **/
ara::com::FindServiceHandle findhandle_pkg{PKG_SERVICE_ID, 0, SD_PORT};
std::shared_ptr<ara::ucm::pkgmgr::proxy::PackageManagementProxy> pkg_proxy_ptr;
/** OTA Trigger in Proxy    **/
ara::com::FindServiceHandle findhandle_ota_triggerin{SM_OTA_TRIGGERIN_SERVICE_ID, 0, SD_PORT};
std::shared_ptr<ara::sm::triggerin::proxy::Trigger_In_OTA_Proxy> ota_triggerin_proxy_ptr;

ara::sm::triggerin::OTA_State ota_state_g = ara::sm::triggerin::OTA_State::OTA_STATE_UNKNOWN;

// create execution client
ExecutionClient client;

int sigval = 0;

int main(void)
{
    cout << endl;
    cout << "\t\t[OTA] Intialization ......" << endl;
    signal(SIGTERM, handle_sigterm); // register signal handler
    cout << "\t\t[OTA] send  execution state running to EM" << endl<<endl;
    client.ReportExecutionState(ExecutionState::kRunning); // report execution state to the execution server

    server_udp_socket.OpenSocket(UDP_PORT_EVENTS);
    server_udp_socket.BindServer();

    /** create package management proxy **/
    cout << "-----------------------------------------------------------------" << endl;
    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle handle_pkg = (ara::ucm::pkgmgr::proxy::PackageManagementProxy::FindService(findhandle_pkg)[0]);
    handle_pkg.UDP_port = UDP_PORT_EVENTS;
    pkg_proxy_ptr = std::make_shared<ara::ucm::pkgmgr::proxy::PackageManagementProxy>(handle_pkg);

    /** create OTA Trigger in proxy **/
    ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle handle_ota = ara::sm::triggerin::proxy::Trigger_In_OTA_Proxy::FindService(findhandle_ota_triggerin)[0];
    cout << "-----------------------------------------------------------------" << endl;
    handle_ota.UDP_port = UDP_PORT_EVENTS;
    ota_triggerin_proxy_ptr = std::make_shared<ara::sm::triggerin::proxy::Trigger_In_OTA_Proxy>(handle_ota);

    cout << "[OTA] Starting OTA process" << endl;
    cout << "handle pkg : " << handle_pkg.m_server_com.port_number << " " << handle_pkg.m_server_com.service_id << endl;
    cout << "handle ota : " << handle_ota.m_server_com.port_number << " " << handle_ota.m_server_com.service_id << endl;
    cout << "-----------------------------------------------------------------" << endl;
    ota_state_g = ara::sm::triggerin::OTA_State::OTA_STATE_INITIALIZED;
    ota_triggerin_proxy_ptr->trigger.Set(ota_state_g);

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
void handle_sigterm(int sig)
{
    sigval = 1; // set signal value will be used as flag
    cout << "[OTA] terminating" << endl;
    client.ReportExecutionState(ExecutionState::kTerminating);
    exit(0);
}

/**
 * @brief Thread 0 used for main code of the OTA client
 *
 * @param v_var
 * @return void*
 */
void *pthread0(void *v_var)
{

    std::cout << std::endl;

    ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput sw_cluster_info = pkg_proxy_ptr->GetSwClusterInfo();
    cout << "------------------- Software Clusters information -------------------------" << endl;
    // loop on sw_cluster_info and print them in formated way
    for (auto &sw_cluster : sw_cluster_info.SwInfo)
    {
        cout << "\tSw Cluster Name    : " << sw_cluster.Name << endl;
        cout << "\tSw Cluster Version : " << sw_cluster.Version << endl;
        cout << "\tSw Cluster State   : " << sw_cluster.State << endl;  
        cout << "-----------------------------------------------------------------" << endl;
    }


    std::cout << std::endl;

    while (true)
    {
        // creating the cloud client and connecting to the server
        cout<<"-----------------------------------------------------------------"<<endl;
        std::cout << "[OTA] connecting to the cloud server ..." << std::endl;
        Client cloud;

        if (cloud.cloudConnect(OTA_IP_CLOUD, OTA_PORT_CLOUD))
        {

            std::cout << "\t[OTA] connection succeeded ..." << std::endl;

            // requesting the new metaData from the cloud server
            std::string json;
            std::vector<MetaData> metaData_v;
            cloud.requestMetadata(metaData_v);
            cout << "-----------------------------------------------------------------" << endl;
            cout << "[OTA] received metaData from cloud server : " << endl;
            for (auto &metaData : metaData_v)
            {

                cout << metaData.serializeToJson() << endl;
            }
            cout << "-----------------------------------------------------------------" << endl;

            // MetaData new_metaData(json);

            // retrieve the old meta-data stored in the file
            MetaDataStorage fileSystem(META_DATA_FILE_PATH);
            std::vector<MetaData> metaDataList = fileSystem.load_MetaData();
            std::size_t listSize = metaDataList.size();
            vector<MetaData> new_metaData_v;


            // check if the new meta-data is different from the old one or if there are new meta-data
            if (listSize == 0)
            {
                std::cout << "[OTA] no meta-data found in the file system" << std::endl;
                std::cout << "[OTA] creating new meta-data" << std::endl;
                new_metaData_v = metaData_v;
            }
            else
            {
                std::cout << "[OTA] meta-data found in the file system" << std::endl;
                std::cout << "[OTA] checking if the meta-data is different from the old one" << std::endl;
                // loop on the new meta-data and check if it is different from the old one
                for (auto &metaData : metaData_v)
                {
                    bool isDifferent = false;
                    for (auto &oldMetaData : metaDataList)
                    {
                        if (metaData == oldMetaData && metaData > oldMetaData)
                        {
                            isDifferent = true;
                        }
                    }
                    if (isDifferent)
                    {
                        std::cout << "[OTA] new meta-data found" << std::endl;
                        new_metaData_v.push_back(metaData);
                    }
                }
            }
            std::cout << "[OTA] new meta-data found : " << new_metaData_v.size() << std::endl;
            if(new_metaData_v.size() > 0){
                // loop on the new meta-data and download the packages
                for (auto &metaData : new_metaData_v)
                {
                    std::cout << "[OTA] downloading package " << metaData.get_appName() << std::endl;
                    std::vector<uint8_t> package;
                    cloud.requestPackage(metaData, package);

                    // if the package is directed for the classic platform use flashing adapter proxy
                    if (metaData.get_platformName()=="classic")
                    {
                        std::cout << "\t[OTA] sending the package to the flashing adapter ..." << std::endl;

                        /** start sending the package to the ucm **/
                        std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> result; /* Saves TransferStartOutput */
                        std::vector<uint8_t> small_data;

                        uint64_t package_size = package.size();
                        result = pkg_proxy_ptr->TransferStart(package_size);
                        ara::ucm::pkgmgr::PackageManagement::TransferStartOutput transfer_start_output = result.get();

                        int block_counter = 0;
                        for (int i = 0; i < package.size(); i++)
                        {
                            for (int j = 0; j < transfer_start_output.BlockSize; j++)
                            {
                                if (i * transfer_start_output.BlockSize + j >= package.size())
                                {
                                    small_data.resize(transfer_start_output.BlockSize);
                                    break;
                                }
                                else
                                    small_data.push_back(package[i * transfer_start_output.BlockSize + j]);
                            }

                            // don't change 64 (packagemanagementskeleton.cpp)
                            std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> result2 =
                                pkg_proxy_ptr->TransferData(transfer_start_output.id, small_data, block_counter); /* Saves TransferDataOutput */

                            ara::ucm::pkgmgr::PackageManagement::TransferDataOutput result3;
                            result3 = result2.get();
                            block_counter++;
                            small_data.clear();
                            if (block_counter * transfer_start_output.BlockSize > package.size())
                                break;
                        }

                        pkg_proxy_ptr->TransferExit(transfer_start_output.id);

                        /** end of sending the package to the ucm **/

                        // /* process sw package */
                        // pkg_proxy_ptr->ProcessSwPackage(transfer_start_output.id);
                        // std::cout << "\t[OTA] package processed ..." << std::endl;
                        // // Activate the new package
                        // ara::ucm::pkgmgr::PackageManagement::ActivateOutput activate_result = pkg_proxy_ptr->Activate();
                        // std::cout << "\t[OTA] package activated ..." << std::endl;
                        
                        // // update the meta-data in the file system
                        if (1)//(activate_result.error == 0)
                        {
                            // updating the stored meta-data
                            std::cout << "\t[OTA] updating the stored meta-data ..." << std::endl;
                            fileSystem.save_MetaData(metaData);
                        }
                        else
                        {
                            // the package failed to be fetched
                            std::cout << "\t[OTA] (rollback) package failed to be flashed ..." << std::endl;
                        }
                    }
                    else if (metaData.get_platformName()=="adaptive")
                    {
                        // TO DO: use the adaptive ucm proxy
                        cout<<"\t[OTA] Adaptive platform not yet implemented"<<endl;
                    }
                    else
                    {
                        std::cout << "\t[OTA] unsupported platform ..." << std::endl;
                    }
                }
            }
            else{
                std::cout << "[OTA] no new versions in the cloud ..." << std::endl;
            }

            // disconnecting from the cloud connection
            cloud.cloudDisconnect();
        }
        else
        {
            std::cout << "\t[OTA] connection failed..." << std::endl;
        }

        sleep(FREQUENCY);

    } // end of while(true)
}

/**
 * @brief  Thread 1 used for handling events of OTA client
 *
 * @param v_var
 * @return void*
 */
void *pthread1(void *v_var)
{
    while (1)
    {
        sockaddr_in echoClntAddr;                    /* Address of datagram source */
        unsigned int clntLen = sizeof(echoClntAddr); /* Address length */

        std::vector<uint8_t> msg; /* Buffer for storing received datagram */
        uint32_t msg_size;        /* Size of received message */

        /* Receive size of the message */
        server_udp_socket.UDPRecFrom((void *)&msg_size, sizeof(msg_size), (struct sockaddr *)&echoClntAddr, &clntLen);
        msg.reserve(msg_size); /* Reserve memory for received message */
        /* Receive the message */
        server_udp_socket.UDPRecFrom((void *)&msg[0], msg_size, (struct sockaddr *)&echoClntAddr, &clntLen);
        cout << "\t[CLIENT]  ->> Handling client " << inet_ntoa(echoClntAddr.sin_addr) << " " << echoClntAddr.sin_port << endl;

        ara::com::proxy_skeleton::Client_udp_Info cudp;            /* Client_udp_Info */
        cudp.port = echoClntAddr.sin_port;                         /* Port of client */
        cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr)); /* Address of client */

        // make sure that the message is SOMEIP
        if (msg[14] != 0x02)
        {

            ara::com::SOMEIP_MESSAGE::Message Nmsg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg); /* Deserialize message */
            msg = Nmsg.GetPayload();                                                                      /* Get payload */

            if (Nmsg.MessageId().serivce_id == pkg_proxy_ptr->GetServiceId())
            {
                if (Nmsg.MessageId().method_id & 0x7FFF == pkg_proxy_ptr->CurrentStatus.Get_event_id())
                { //
                    pkg_proxy_ptr->CurrentStatus.handlecall(msg);
                    std::cout << "NEW EVENT1 : " << pkg_proxy_ptr->CurrentStatus.get_value() << std::endl;
                }
                else
                {
                    ///@todo Send Error Message unknown event_id
                }
            }
            else
            {
                ///@todo Send Error Message unknown service_id
            }
        }
    }
}
