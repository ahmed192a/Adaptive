/**
 * @file ota_main.cpp
 * @author 
 * @brief ota proccess main function
 ********************************************************************************/

#include <iostream>
#include <string>
#include "OTA/meta_data_storage.hpp"
#include "OTA/client.hpp"

#define META_DATA_FILE_PATH "./meta-data.dat"

using namespace ota;

int main(void) {

    std::cout << std::endl << "[OTA] started ..." << std::endl;

    // creating the cloud client and connecting to the server
    std::cout << "[OTA] connecting to the cloud server ..." << std::endl;
    Client cloud;
    
    if( cloud.cloudConnect(IP_CLOUD, PORT_CLOUD) ) {
        std::cout << "[OTA] connection succeeded ..." << std::endl;
    }
    else {
        std::cout << "[OTA] connection failed..." << std::endl;
    }

    // requesting the metaData
    char array[BUFFER_SIZE];
    cloud.requestMetadata(array);
    std::string json = array;


    MetaData metaData( json );


    std::cout << metaData << std::endl;
    
    // // The instance that will deal with storing and retieving the meta-data
    // MetaDataStorage fileSystem(META_DATA_FILE_PATH);


    // // std::string json = """{\"appID\": \"K134\",\"appName\":\"OTA_APP\",\"sizeInBytes\":137,\"platformName\":\"adaptive\",\"version\": \"1.0.4\",\"result\":\"ok\"}""";
    // // communication with the cloud to get the meta-data in the form of json string


    // MetaData metaData( std::string(json) );

    // // after some logical proccessing 

    // fileSystem.save_MetaData(metaData);


    
    return 0;
}