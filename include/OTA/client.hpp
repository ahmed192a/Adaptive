#ifndef OTA_CLIENT_H
#define OTA_CLIENT_H

#include <iostream> //string
#include <arpa/inet.h> //inet_addr
#include <vector>

#define OTA_IP_CLOUD "127.0.0.1"
#define OTA_PORT_CLOUD 8888
#define OTA_PACKAGE_BUFFER_SIZE 10000
#define OTA_METADATA_BUFFER_SIZE 1000

namespace OTA{

class Client
{
private:
        int sock;
        struct sockaddr_in server;
        std::string address;
        int port;

        bool sendData(std::string data);


    public:

        Client();
    /**
     *  @brief Connects the OTA application to the cloud server.
     *
     *  @details
     *   Connects the OTA application to the cloud server which
     *   has the update package and its metadata. 
     * 
     *  @param address  IPV4 address of the cloud server.
     *  @param port The port number to connect to on the cloud server.
     *  @return     Returns zero in case failed to connect to the cloud server.
     */

        bool cloudConnect(std::string address, int port);

    
    
    
    /**
     *  @brief Requests the package metadata from the cloud server.
     *
     *  @details
     *   Requests the package metadata from the cloud server. 
     *   The package metadata has information like appID, appName,... 
     * 
     *  @param data  A pointer to characters to store the requested metadata in.
     *  @return     Returns zero in case failed to get the package metadata from the cloud server.

     */

        bool requestMetadata(std::string &data);

    
    
    
    /**
     *  @brief Requests the package from the cloud server.
     *
     *  @details
     *   Requests the package from the cloud server. 
     *   The package is the update itself
     * 
     *  @param data  A pointer to characters to store the requested package in.
     *  @return     Returns zero in case failed to get the package from the cloud server.

     */

        bool requestPackage(std::vector<uint8_t> &data);



    /**
     *  @brief Disconnects the OTA application to the cloud server.
     *
     *  @details
     *   Disconnects the OTA application to the cloud server.
     * 
     *  @param   
     *  @return     

     */
        void cloudDisconnect();
};

}


#endif