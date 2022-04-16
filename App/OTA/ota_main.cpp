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
        
        if( cloud.cloudConnect(OTA_IP_CLOUD, OTA_PORT_CLOUD) )
        {

            std::cout << "\t[OTA] connection succeeded ..." << std::endl;

            // requesting the new metaData from the cloud server
            char json_ptr[OTA_METADATA_BUFFER_SIZE];
            cloud.requestMetadata(json_ptr);
            std::string json = json_ptr;
            MetaData new_metaData(json);
            
            // retrieve the old meta-data stored in the file 
            MetaDataStorage fileSystem(META_DATA_FILE_PATH);
            std::vector<MetaData> metaDataList = fileSystem.load_MetaData();
            std::size_t listSize = metaDataList.size();
            MetaData old_metaData;

            // getting the meta data of the same applicaton 
            for(std::size_t i = (listSize - 1); i  >= 0; i--)
            {
                if(new_metaData == metaDataList[i])
                {
                    old_metaData = metaDataList[i];
                    break;
                }
            }

            // // comparing the application meta-data with old one stored in the file system
            if(new_metaData.get_version() > old_metaData.get_version()){
                
                std::cout << "\t[OTA] downloading the new package ..." << std::endl;
                
                // downloading the package from the cloud
                char package_ptr[OTA_PACKAGE_BUFFER_SIZE];
                cloud.requestPackage(package_ptr);
                std::string package = package_ptr;

                std::cout << "\t[OTA] sending the package to the flashing adapter ..." << std::endl;

                /** here should be the logic of sending the package binary to the flashing adapter**/
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



    return 0;
}