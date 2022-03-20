
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
            cout<<"Could not create socket";
            return false;

        }

        cout<<"Socket created\n";
    }
    else { /* OK , nothing */ }
    
    
    //Configure the server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr( address.c_str() );
    server.sin_port = htons( port );

    //Connect to remote server
    if( connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0 )
    {
        cout<<"connect failed. Error";
        return false;
    }

    cout<<"Connected\n";
    return true;
}

/*
    Send data to the connected host
*/
bool Client::sendData(string data)
{
    cout<<"Sending data...";
    cout<<data;
    cout<<"\n";
    
    // Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        cout<<"Send failed";
        return false;
    }
    
    cout<<"Data sent\n";

    return true;
}




bool Client::requestMetadata(std::string  * data){

    char buffer [OTA_METADATA_BUFFER_SIZE];
    if(this->sendData("Requesting Metadata")==0){
        return false;
    };
    
    //Receive a reply from the server
    if( recv(sock ,buffer , OTA_METADATA_BUFFER_SIZE, 0) < 0)
    {
        cout<<"recv failed";
        return false;
    }
    cout<<"Received Metadata: ";
    *data=buffer;
    return true;
    
}

bool Client::requestPackage(char * data){


    if(this->sendData("Requesting Package")==0){
        return false;
    };
    //Receive a reply from the server
    if( recv(sock ,data ,OTA_PACKAGE_BUFFER_SIZE , 0) < 0)
    {
        cout<<"recv failed";
        return false;
    }
    cout<<"Received Package: ";
   return true;
    
}

void Client::cloudDisconnect(){
    this->sendData("End Connection");
    close(sock);
}



int main(int argc , char *argv[])
{

    Client c;

    //connect to the cloud
    c.cloudConnect(OTA_IP_CLOUD , OTA_PORT_CLOUD);

    //get metadata

    string metadata;
    c.requestMetadata(&metadata);
    cout<<metadata<<endl;

    string metadata2;
    c.requestMetadata(&metadata2);
    cout<<metadata2<<endl;
    

    //get package
    char package [OTA_PACKAGE_BUFFER_SIZE];
    c.requestPackage(package);
    cout<<package<<endl;
   
    //Disconnect to the cloud after finishing
    c.cloudDisconnect();



    //done
    return 0;
}