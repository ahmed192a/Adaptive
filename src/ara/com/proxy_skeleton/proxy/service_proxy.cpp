/**
 * @file service_proxy.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "service_proxy.h"
#include <iostream>

struct C_Info
{
    int process_id;
    char method_name[30];
    int param1;
    int param2;
};

namespace ara
{
namespace com
{
namespace proxy_skeleton
{
namespace proxy
{
    int ServiceProxy::FindService(int portNumber, int service_id)
    {
        // Send a service id to the service discovery
        // receive a struct
        char buffer[256];
        char hostbuffer[256];
        CClient c1(SOCK_STREAM);
        c1.OpenSocket();
        bzero(hostbuffer,256);
        int hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

        if(hostnameRet < 0)
        {
            std::cout<<("Unable to local machine get Host Name\n");
        }

        c1.GetHost("127.0.0.1", portNumber);
        c1.ClientConnect();

        // send the service id
        c1.ClientWrite(&service_id, sizeof(int));

        // receive a struct        
        c1.ClientRead(&this->receive, sizeof(struct SD_data));
        std::cout << "Received port number: " << receive.port_number << "  " << receive.process_id << std:: endl;
        std::cout << "\n=> Connection terminated.\nGoodbye...\n";

        // we then call the setter function to set its private data, that later will be used to subscribe to an event
        setter(receive.port_number, receive.process_id);
        c1.CloseSocket();
        return 0;
    }


    // template <typename... Args>
    int ServiceProxy::SendRequest()
    {
        int bufsize = 1024;
        char buffer[bufsize];
        char hostbuffer[256];
        CClient c1(SOCK_STREAM);
        c1.OpenSocket();
        bzero(hostbuffer,256);
        std::cout<<"REQUEST"<<std::endl;
        int hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

        if(hostnameRet < 0)
        {
            std::cout<<("Unable to local machine get Host Name\n");
        }

        // talk to the server using the received port number
        c1.GetHost("127.0.0.1", this->receive.port_number);
        c1.ClientConnect();

        // Receive a confirmation message from the server
        std::cout << "=> Awaiting confirmation from the server2..." << std::endl; //line 40
        bzero(buffer, bufsize);
        c1.ClientRead(buffer, 256);
        std::cout << buffer<<std::endl;
        std::cout << "=> Connection confirmed, you are good to go...";

        
        struct C_Info x = {getpid(), "add", 3, 2};

        // send the requested method, and the parameters
        c1.ClientWrite(&x, sizeof(struct C_Info));

        std::cout << "The method is sent to the server" << std::endl;

        int result; // to save the result of the method

        // receive the methods result
        c1.ClientRead((int*)&result, sizeof(int));
        std::cout << "Received result: " << result << std::endl;
        std::cout << "\n=> Connection terminated.\nGoodbye...\n";

        c1.CloseSocket();

        return 0;        
    }
    ServiceProxy::ServiceProxy()
    {

    }
    ServiceProxy::~ServiceProxy()
    {

    }

}
}
}
}

