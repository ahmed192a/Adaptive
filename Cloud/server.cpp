#include <unistd.h>// close socket
#include <sys/socket.h>//socket
#include <arpa/inet.h> //inet_addr
#include <iostream>
#include <fstream>

#define PORT 8888
#define PACKAGE_FILE "package.dat"
#define METADATA_FILE "metadata.dat"
#define BUFFER_SIZE 100000


using namespace std;
int main(int argc, char const *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		cout<<"socket failed";
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
	{
		cout<<"bind failed";
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		cout<<"listen";
		exit(EXIT_FAILURE);
	}
    while(1){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
        {
            cout<<"accept";
            exit(EXIT_FAILURE);
        }
        while(1){
            	char buffer[50] = {0};
                string temp;
                read( new_socket , buffer, 50);
                temp=buffer;
                cout<<"Client sent: "<<temp<<endl; 
                int i=0;
                if(temp=="Requesting Metadata"){
                    ifstream metadataFile;
                    metadataFile.open(METADATA_FILE,ios::in);
                                      
                    char metadata[BUFFER_SIZE];
                    while(!metadataFile.eof()){
                        
                        metadataFile.read((char*) &metadata[i],1);
                        i++;
                    }
                    metadataFile.close();
					if( send(new_socket ,  metadata , i-1, 0) < 0) 
                    {
                        cout<<"Send Error";
                    }
                    cout<<"Metadata sent\n";

                }
                else if (temp=="Requesting Package")
                {
                    ifstream packageFile;
                    packageFile.open(PACKAGE_FILE,ios::in);
                                      
                    char packageData[BUFFER_SIZE];
                    while(!packageFile.eof()){
                        
                        packageFile.read((char*) &packageData[i],1);
                        i++;
                    }
                    packageFile.close();
					if( send(new_socket ,  packageData , i-1 , 0) < 0) 
                    {
                        cout<<"Send Error";
                    }
                    cout<<"Package sent\n";

                }
                else if (temp=="End Connection")
                {
                    cout<<"Connection ended\n";
                    break;
                }
                
        }
    }
	return 0;
}
