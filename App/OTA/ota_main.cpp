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

#define META_DATA_FILE_PATH "./meta-data.dat"
#define FREQUENCY 10 // 10 seconds

using namespace OTA;

int main(void) {

    std::cout << std::endl << "[OTA] started ..." << std::endl;

    while(true)
    {
        // creating the cloud client and connecting to the server
        std::cout << "[OTA] connecting to the cloud server ..." << std::endl;
        Client cloud;
        
        if( true /*cloud.cloudConnect(OTA_IP_CLOUD, OTA_PORT_CLOUD) */)
        {


            std::cout << "[OTA] connection succeeded ..." << std::endl;


            // requesting the new metaData from the cloud server
            std::string json = """{\"appID\": \"K134\",\"appName\":\"OTA_APP\",\"sizeInBytes\":137,\"platformName\":\"adaptive\",\"version\": \"1.0.4\",\"result\":\"ok\"}""";
            // cloud.requestMetadata(&json);
            MetaData new_metaData(json);
            

            // retrieve the latest meta-data stored in the file 
            MetaDataStorage fileSystem(META_DATA_FILE_PATH);
            MetaData old_metaData;
            fileSystem.retrieve_LatestMetaData(old_metaData);

            
            // // comparing the application meta-data with old one stored in the file system
            if(new_metaData.get_version() > old_metaData.get_version()){
                std::cout << "\t[OTA] downloading the new package ..." << std::endl;
                fileSystem.save_MetaData(new_metaData);
            }
            else {
                std::cout << "\t[OTA] no new versions in the cloud ..." << std::endl;
            }


            // disconnecting from the cloud connection
            // cloud.cloudDisconnect();

        }
        else {
            std::cout << "[OTA] connection failed..." << std::endl;
        }

        sleep(FREQUENCY);

    } // end of while(true)



    return 0;
}