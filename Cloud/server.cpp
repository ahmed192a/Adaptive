/**
 * @file server.cpp
 * @author Flashing Adapter Graduation Project Team
 * @brief 
 * @version 0.1
 * @date 2022-07-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <unistd.h>// close socket
#include <sys/socket.h>//socket
#include <arpa/inet.h> //inet_addr
#include <iostream>
#include <fstream>
#include <vector>

#define PORT 8888
#define PACKAGE_FILE "flash_tiva.out"
#define METADATA_FILE "metadata.dat"
#define BUFFER_SIZE 100000


using namespace std;
std::vector<char> ReadAllBytes(char const *filename)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);
    return result;
}
int main(int argc, char const *argv[])
{
    cout << endl;
    cout<<"cloud Intialization ...";
    cout << "cloud pid : " << getpid()<< endl;
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		cout<<"\t socket failed";
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
	{
		cout<<"\t bind failed";
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		cout<<"\t [Cloud] listen ... ";
		exit(EXIT_FAILURE);
	}
    cout << "[cloud] Waiting for client ...." << endl;
    while(1){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
        {
            cout << "------------------------------------" << endl;
            cout<<"\t [cloud] accept new client";
            exit(EXIT_FAILURE);
        }
        while(1){
            	char buffer[50] = {0};
                string temp;
                read( new_socket , buffer, 50);
                temp=buffer;
                cout<<"\t [cloud] sent: "<<temp<<endl; 
                int i=0;
                if(temp=="\t [cloud] Requesting Metadata"){
                    // ifstream metadataFile;
                    // metadataFile.open(METADATA_FILE,ios::in);
                                      
                    // char metadata[BUFFER_SIZE];
                    // while(!metadataFile.eof()){
                        
                    //     metadataFile.read((char*) &metadata[i],1);
                    //     i++;
                    // }
                    // metadataFile.close();

                    std::vector<char> metadata = ReadAllBytes(METADATA_FILE);

                    int metaDataSize = metadata.size() ;
                    send(new_socket ,  &metaDataSize , sizeof(metaDataSize) , 0);
					if( send(new_socket ,  metadata.data() , metaDataSize, 0) < 0) 
                    {
                        cout<<"\t Send Error";
                    }
                    cout<<"\t [Cloud] send Metadata \n";

                }
                else if (temp=="Requesting Package")
                {
                    // ifstream packageFile;
                    // packageFile.open(PACKAGE_FILE,ios::in);
                                      
                    // char packageData[BUFFER_SIZE];
                    // while(!packageFile.eof()){
                        
                    //     packageFile.read((char*) &packageData[i],1);
                    //     i++;
                    // }
                    // packageFile.close();
                    std::vector<char> packageData = ReadAllBytes(PACKAGE_FILE);

                    int packageDataSize = packageData.size() ;
                    send(new_socket ,  &packageDataSize , sizeof(packageDataSize) , 0);

					if( send(new_socket ,  packageData.data() , packageDataSize , 0) < 0) 
                    {
                        cout<<"\t Send Error";
                    }
                    cout<<"\t [Cloud] send Package \n";

                }
                else if (temp=="\t End Connection")
                {
                    cout<<"\t [Cloud] Connection ended\n";
                    break;
                }
                
        }
    }
	return 0;
}
