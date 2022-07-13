
#include "OTA/client.hpp"
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <unistd.h>// close socket

using namespace std;
using namespace OTA;

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
    if( send(sock , &data[0] , data.length() , 0) < 0)
    {
        // cout<<"Send failed";
        return false;
    }
    
    // cout<<"Data sent\n";

    return true;
}




bool Client::requestMetadata(std::vector<MetaData> &metadata_v){

    // send request to the server
    string request = "Requesting Metadata";
    int size = request.length();

    if(send(sock , &size , sizeof(size) , 0) < 0)
    {
        cout<<"Send size failed"<<endl;
        return false;
    }
    if(send(sock , &request[0] , request.length() , 0) < 0)
    {
        cout << "Send request failed" << endl;
        return false;
    }

    // if(this->sendData("Requesting Metadata")==0){
    //     return false;
    // };
    
    //Receive a reply from the server
    
    int metaDataSize;
    if (recv(sock, &metaDataSize, sizeof(metaDataSize), 0) < 0)
    {
        cout<<"\t[CLOUD] recv metadata size failed"<<endl;
        return false;
    }
    std::vector<uint8_t> metadata;
    metadata.resize(metaDataSize);
    if( recv(sock ,&metadata[0] , metaDataSize, 0) < 0)
    {
        cout<<"\t[CLOUD] Error receiving metadata"<<endl;
        return false;
    }
    // deserialize metadata
    string metadata_str;
    for(int i=0;i<metadata.size();i++){
        if(metadata[i] == 0){
            MetaData md(metadata_str);
            metadata_v.push_back(md);
            metadata_str = "";
            continue;
        }
        metadata_str += metadata[i];
    }
    return true;
    
}

bool Client::requestPackage(MetaData metadata, std::vector<uint8_t> &data){
    //serialize metadata
    std::string metadata_str = metadata.serializeToJson();
    cout<<"\t[CLOUD] request the package of metadata: "<<metadata_str<<endl;
    string data_str = "Requesting Package";
    int data_str_size = data_str.length();

    if (send(sock, &data_str_size, sizeof(data_str_size), 0) < 0)
    {
        cout<<"\t[CLOUD] send data size failed"<<endl;
        return false;
    }
    if (send(sock, &data_str[0], data_str_size, 0) < 0)
    {
        cout<<"\t[CLOUD] send data failed"<<endl;
        return false;
    }

    // if(this->sendData()==0){
    //     return false;
    // };


    // Send metadata
    int metaDataSize = metadata_str.size();
    if( send(sock , &metaDataSize , sizeof(metaDataSize), 0) < 0)
    {
        cout<<"\t[CLOUD] send metadata size failed"<<endl;
        return false;
    }

    if( send(sock , &metadata_str[0] , metaDataSize, 0) < 0)
    {
        cout<<"\t[CLOUD] send metadata failed"<<endl;
        return false;
    }

    //Receive a reply from the server
    int packageDataSize;
    if (recv(sock, &packageDataSize, sizeof(packageDataSize), 0) < 0)
    {
        cout<<"\t[CLOUD] recv package size failed"<<endl;
        return false;
    }
    data.clear();
    data.resize(packageDataSize);
    if(recv(sock ,data.data() ,packageDataSize , 0) < 0)
    {
        cout<<"\t[CLOUD] recv package failed"<<endl;
        return false;
    }
   return true;
}

void Client::cloudDisconnect(){
    string data = "End Connection";
    int size = data.length();
    if(send(sock , &size , sizeof(size) , 0) < 0)
    {
        cout<<"Send size failed"<<endl;
        return;
    }
    if(send(sock , &data[0] , data.length() , 0) < 0)
    {
        cout << "Send request failed" << endl;
        return;
    }
    // this->sendData("End Connection");
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