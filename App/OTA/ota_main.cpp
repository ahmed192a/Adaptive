/**
 * @file ota_main.cpp
 * @author 
 * @brief ota proccess main function
 ********************************************************************************/

#include <iostream>
#include "OTA/meta_data_storage.hpp"
#include "OTA/client.hpp"

#define META_DATA_FILE_PATH "./testFile.dat"

int main(void) {

    std::cout << std::endl << "[OTA] started ..." << std::endl << std::endl;

    // creating the cloud client
    std::cout << std::endl << "[OTA] connecting to the cloud server ..." << std::endl << std::endl;
    Client cloud;
    while( !cloud.cloudConnect(IP_CLOUD, PORT_CLOUD) ) {
        std::cout << std::endl << "[OTA] failed to connect ..." << std::endl << std::endl;
        sleep(1);
    }

    
    // The instance that will deal with storing and retieving the meta-data
    MetaDataStorage fileSystem(META_DATA_FILE_PATH);


    std::string json = """{\"appID\": \"K134\",\"appName\":\"OTA_APP\",\"sizeInBytes\":137,\"platformName\":\"adaptive\",\"version\": \"1.0.4\",\"result\":\"ok\"}""";
    // communication with the cloud to get the meta-data in the form of json string


    MetaData metaData(json);

    // after some logical proccessing 

    fileSystem.save_MetaData(metaData);


    
    return 0;
}