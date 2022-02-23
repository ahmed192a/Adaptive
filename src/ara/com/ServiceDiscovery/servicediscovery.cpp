#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define N 10

using namespace std;

// SD: service discovery 
struct SD_data{
    int service_id;
    int process_id;
    int port_number;
};


int main(int argc, char **argv)
{
    int portNum = atoi(argv[1]);
    struct SD_data shared_mem[N]; // where to save the service information 
    // Receiving Service information from the server
    {
        /* UDP */        
        int udpServer;
        struct sockaddr_in udpservaddr, cliaddr;
        
        // Creating socket file descriptor
        if ((udpServer = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&udpservaddr, 0, sizeof(udpservaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));
        // Filling server information
        udpservaddr.sin_family = AF_INET; // IPv4
        udpservaddr.sin_addr.s_addr = INADDR_ANY;
        udpservaddr.sin_port = htons(portNum);

        int yes = 1;
        if (setsockopt(udpServer, SOL_SOCKET, SO_REUSEADDR,
                                (void*)&yes, sizeof(yes)) < 0) {
        // fprintf(stderr, "setsockopt() failed. Error: %d\n", GETSOCKETERRNO());
            cout<<"ERROR---------\n";
        }
        // Bind the socket with the server address
        if (bind(udpServer, (const struct sockaddr *)&udpservaddr,
                sizeof(udpservaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        socklen_t len;
        int n;

        len = sizeof(cliaddr);  //len is value/resuslt

        // receiving the struct from the server
        n = recvfrom(udpServer, &shared_mem[0], sizeof(struct SD_data), 
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
            
        printf("Struct: \n");
        cout << shared_mem[0].port_number << " ";
        cout << shared_mem[0].service_id << " ";
        cout << shared_mem[0].process_id << endl;

        close(udpServer);
        /* End */
    }    

    /* TCP Initialiazation */
    int tcpServer, server;
    bool isExit;
    int bufsize = 1024;
    char buffer[bufsize];
    int service_number;
    int portNumber = -1; // if the service is not in the memory, send -1 

    struct sockaddr_in tcpServaddr;
    socklen_t size;

    tcpServer = socket(AF_INET, SOCK_STREAM, 0);

    if (tcpServer < 0) 
    {
        printf("\nError establishing socket...\n");
        exit(1);
    }

    tcpServaddr.sin_family = AF_INET;
    tcpServaddr.sin_addr.s_addr = htons(INADDR_ANY);
    tcpServaddr.sin_port = htons(portNum);


	int yes = 1;
	if (setsockopt(tcpServer, SOL_SOCKET, SO_REUSEADDR,
	                        (void*)&yes, sizeof(yes)) < 0) {
	   // fprintf(stderr, "setsockopt() failed. Error: %d\n", GETSOCKETERRNO());
		cout<<"ERROR---------\n";
	}
    if ((bind(tcpServer, (struct sockaddr*)&tcpServaddr,sizeof(tcpServaddr))) < 0) 
    {
        printf("=> Error binding connection, the socket has already been established...\n");
        return -1;
    }
    /*End */

    //////////////////////////////////////////////////////////////////
    listen(tcpServer, 1);
    int clientCount = 1;
    while(1)
    {
        size = sizeof(tcpServaddr);
        server = accept(tcpServer,(struct sockaddr *)&tcpServaddr,&size);

        // first check if it is valid or not
        if (server < 0) 
            cout << "=> Error on accepting..." << endl;

        while (server > 0) 
        {
            strcpy(buffer, "=> Server connected...\n");
            send(server, buffer, bufsize, 0);
            cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << endl;
            cout << "\n=> Enter # to end the connection\n" << endl;

            /* 
                Note that we would only get to this point after a 
                client has successfully connected to our server. 
                This reads from the socket. Note that the read() 
                will block until there is something for it to read 
                in the socket, i.e. after the client has executed a 
                the send().

                It will read either the total number of characters 
                in the socket or 1024
            */

            cout << "Client: ";

            // receive the requested service number
            recv(server, &service_number, sizeof(int), 0);
            cout << "Received service number: " << service_number << endl;

            // search the memory for the requested service 
            for(int j = 0; j < N; j++)
            {
                // portNumber = 1608;
                if(shared_mem[j].service_id == service_number)
                {
                    portNumber = shared_mem[j].port_number;
                }
            }

            // send the port number to the client
            send(server, &portNumber, sizeof(int), 0);

            // inet_ntoa converts packet data to IP, which was taken from client
            cout << "\n\n=> Connection terminated with IP " << inet_ntoa(tcpServaddr.sin_addr);
            close(server);
            cout << "\nGoodbye..." << endl;
            isExit = false;
            break;
            // exit(1);
        }
    }
    
    close(tcpServer);

    return 0;
}