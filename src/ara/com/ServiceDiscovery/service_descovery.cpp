#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>

#include "data.h"
#include "csv.hpp"
#include "Service_Discovery/server/CServer.h"

#define CSV_FILE "data.csv"

using namespace std; 

int main(){
    int portNumber = 1690;    
    int process_id = fork();  
    vector<SD_data> data; 
    struct SD_data receive;  
    CSV csv;
    // use the child process for sercice discovery (Listen to all servers and get services information)
    if (process_id == 0){
        // listen to all servers 
        // save process id, service id, and port number into the csv file
        CServer s1(SOCK_DGRAM);
        s1.OpenSocket(portNumber);
        s1.BindServer();

        struct sockaddr_in cliaddr;
        socklen_t len = sizeof(cliaddr);
        while(1){            
            cout << "xx" << endl;
            // receive a struct containing the service information
            s1.UDPRecFrom(&receive, sizeof(struct SD_data), (struct sockaddr *) &cliaddr, &len);
            printf("Struct: \n");
            data.push_back(receive);
            cout << receive.port_number << " ";
            cout << receive.service_id << " ";
            cout << receive.process_id << endl;
            // write these information into the csv file

            if(receive.message_type)
                csv.write(CSV_FILE, data[0]);
            else
                csv.delete_record(CSV_FILE, receive.service_id);
        }
        s1.CloseSocket();
    }
    // use the main process for service registery (Listen to all clients and provide them info if exists)
    else{
        // wait until a client request a service 
        // if a client requests a service,  search the csv file to find this service 
        CServer s1(SOCK_STREAM);
        int service_id;
        s1.OpenSocket(portNumber);
        s1.BindServer();
        s1.ListenServer(3); 
        while(1){
            s1.AcceptServer();
            // receive the service id
            s1.ReceiveServer(&service_id, sizeof(int));

            // search the file, 
            // it takes a vector of structs "in case there's more than one server offers the service"
            csv.FindRow(CSV_FILE, service_id, data);

            // in the future, a number should be sent first to indicate how many struct is gonna be sent
            // then a for loop to send the vector "containing port numbers" element by element 

            // send the port number to the client
            s1.SendServer(&data[0].port_number, sizeof(int));
            s1.ClientClose();
        }
        
        s1.CloseSocket();

        waitpid (process_id, NULL, 0);

        // while(wait(NULL) > 0){}
    }

    

    return 0;
}


