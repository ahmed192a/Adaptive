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

    while(true) {
        // creating the cloud client and connecting to the server
        std::cout << "[OTA] connecting to the cloud server ..." << std::endl;
        Client cloud;
        
        if( cloud.cloudConnect(OTA_IP_CLOUD, OTA_PORT_CLOUD) ) {
            std::cout << "[OTA]\t connection succeeded ..." << std::endl;


            // requesting the metaData
            std::string json;
            cloud.requestMetadata(&json);

            //////////////////////////////////////////////////////////
            // temporary error handling
            std::size_t size = json.size();
            while(json[size-1] != '}') {
                json.pop_back();
                size--;
                if(size == 0 )
                    break;
            }
            //////////////////////////////////////////////////////////
            MetaData new_metaData(json);


            // // The instance that will deal with storing and retieving the meta-data
            MetaDataStorage fileSystem(META_DATA_FILE_PATH);
            MetaData old_metaData;
            fileSystem.retrive_LatestMetaData(old_metaData);

            
            // // comparing the application meta-data with old one stored in the file system
            if(new_metaData.get_version() > old_metaData.get_version()){
                std::cout << "[OTA] downloading the new package ..." << std::endl;
                fileSystem.save_MetaData(new_metaData);
                break;
            }
            else {
                std::cout << "[OTA] no new versions in the cloud ..." << std::endl;
            }


            // disconnecting from the cloud connection
            cloud.cloudDisconnect();

        }
        else {
            std::cout << "[OTA]\t connection failed..." << std::endl;
        }

        sleep(FREQUENCY);

    } // end of while(true)

    return 0;
}