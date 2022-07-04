
#include "OTA/client.hpp"
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <unistd.h>// close socket
#include "../../../include/ara/crypto/cryp/concrete_crypto_provider.hpp"

using namespace std;
using namespace OTA;
using namespace ara::crypto::cryp;
using namespace ara::crypto;

/*
    constructor
*/
Client::Client()
{
    sock = -1;
    address = "";
    port = 0;
}

/*
    Connect to a host on a certain port number
*/
bool Client::cloudConnect(string address , int port)
{
    // create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            // cout<<"Could not create socket";
            return false;

        }

        // cout<<"Socket created\n";
    }
    else { /* OK , nothing */ }
    
    
    //Configure the server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr( address.c_str() );
    server.sin_port = htons( port );

    //Connect to remote server
    if( connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0 )
    {
        // cout<<"connect failed. Error";
        return false;
    }

    // cout<<"Connected\n";
    return true;
}

/*
    Send data to the connected host
*/
bool Client::sendData(string data)
{
    // cout<<"Sending data...";
    // cout<<data;
    // cout<<"\n";
    
    // Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        // cout<<"Send failed";
        return false;
    }
    
    // cout<<"Data sent\n";

    return true;
}




bool Client::requestMetadata(std::string &data){

    if(this->sendData("Requesting Metadata")==0){
        return false;
    };
    
    //Receive a reply from the server
    
    int metaDataSize;
    recv(sock, &metaDataSize, sizeof(metaDataSize), 0);
    data.resize(metaDataSize);
    if( recv(sock ,&data[0] , metaDataSize, 0) < 0)
    {
        // cout<<"recv failed";
        return false;
    }
    // cout<<"Received Metadata: " << data <<endl;
    return true;
    
}

bool Client::requestPackage(std::vector<uint8_t> &data, std::vector<uint8_t>& sign){


    if(this->sendData("Requesting Package")==0){
        return false;
    };
    //Receive a reply from the server
    int packageDataSize;
    recv(sock, &packageDataSize, sizeof(packageDataSize), 0);
    data.resize(packageDataSize);
    if(recv(sock ,data.data() ,packageDataSize , 0) < 0)
    {
        return false;
    }

    /******************* Added to decrypt ******************************/

    //Receive the signature from the server
    int macSize;
    recv(sock, &macSize, sizeof(macSize), 0);
    sign.resize(macSize);
    if (recv(sock, sign.data(), macSize, 0) < 0)
    {
        return false;
    }

    ara::crypto::cryp::ConcreteCryptoProvider::Uptr a = std::make_unique<ConcreteCryptoProvider>();
    Authentication::Uptr authenticatedpointer = a->CreateAuthCipherCtx(1);
    ara::crypto::cryp::SymmetricKey key;
    key.keyVal = { 'a','a','a','a','s','s','s','s','u','k','j','h','h','h','h','j','h','h','h','h','y','h','u','y','d','y','g','i','y','u','t','u' };
    authenticatedpointer->Transform_set = CryptoTransform::kDecrypt;
    authenticatedpointer->SetKey(key, CryptoTransform::kDecrypt);
    authenticatedpointer->Start();
    std::vector<uint8_t> authenticatedDecrypted = authenticatedpointer->ProcessConfidentialData(data, sign);
    // If authenticatedDecrypted vector is empty,
    if (!(authenticatedDecrypted.size()))
    {
        return false;
    }

    return true;
    
}

void Client::cloudDisconnect(){
    this->sendData("End Connection");
    close(sock);
}



/*int main(int argc , char *argv[])
{

    Client c;

    //connect to the cloud
    c.cloudConnect(OTA_IP_CLOUD , OTA_PORT_CLOUD);

    //get metadata
    string s;

    char metadata [OTA_METADATA_BUFFER_SIZE];
    c.requestMetadata(metadata);
    s=metadata;
    cout<<s<<endl;

    char metadata2 [OTA_METADATA_BUFFER_SIZE];
    c.requestMetadata(metadata2);
    s=metadata2;
    cout<<s<<endl;
    
    char metadata3 [OTA_METADATA_BUFFER_SIZE];
    c.requestMetadata(metadata3);
    s=metadata3;
    cout<<s<<endl;

    //get package
    char package [OTA_PACKAGE_BUFFER_SIZE];
    c.requestPackage(package);
    cout<<package<<endl;
   
    //Disconnect to the cloud after finishing
    c.cloudDisconnect();



    //done
    return 0;
}*/