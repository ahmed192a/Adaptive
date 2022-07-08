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
//global key
std::vector<char> key = { 'a','a','a','a','s','s','s','s','u','k','j','h','h','h','h','j','h','h','h','h','y','h','u','y','d','y','g','i','y','u','t','u' };
std::vector<char> ProcessBlock(std::vector<char> in, bool suppressPadding);
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
                        cout<<"Send Error";
                    }
                    cout<<"Metadata sent\n";

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
                    std::vector<char> encryptedData = ProcessBlock(packageData, false);

                    int packageDataSize = packageData.size() ;
                    send(new_socket ,  &packageDataSize , sizeof(packageDataSize) , 0);

                    if (send(new_socket, encryptedData, encryptedData.size(), 0) < 0)
                    {
                        cout << "Send Error";
                    }
                    cout << "Package sent\n";

                    string plain, mac;
                    // to convert package data to string
                    for (char i = 0; i < packageData.size(); i++)
                    {
                        plain += packageData[i];
                    }
                    HMAC <SHA256> hmac(key, key.size());
                    StringSource ss2(plain, true, newHashFilter(hmac, new StringSink(mac)));
                    int macSize = mac.size();

                    send(new_socket, &macSize, sizeof(macSize));
                    if (send(new_socket, mac, mac.size(), 0) < 0)
                    {
                        cout << "Send Error";
                    }
                    cout << "Mac sent\n";
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

/*Process (encrypt / decrypt) an input block according to the crypto configuration*/
std::vector<char> ProcessBlock(std::vector<char> in, bool suppressPadding)
{


    std::string in_data, out_data;
    std::vector<char> return_data;

    for (char i = 0; i < in.size(); i++)
    {
        in_data += in[i];
    }

    /*raise and error if the boolean parameter {suppressPadding} was set to TRUE and
     the provided input buffer does not match the block-size*/
    if (suppressPadding == true && in.size() != 16)
    {
        //raise CryptoErrorDomain::kInvalidInputSize
    }
    //raise and error if the context was not initialized by calling SetKey()/

    else
    {
        try
        {
            CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;

            CryptoPP::StringSource s(in_data, true,
                new CryptoPP::StreamTransformationFilter(e,
                    new CryptoPP::StringSink(out_data)
                ) // StreamTransformationFilter
            ); // StringSource

        }
        catch (const CryptoPP::Exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }

        //Convert the string result into vector of bytes
        for (uint8_t i = 0; i < out_data.length(); i++)
        {
            return_data.push_back(out_data[i]);
        }

        return return_data;
    }
}


