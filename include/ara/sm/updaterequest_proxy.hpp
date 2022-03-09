/**
 * @file updaterequest_proxy.h
 * @author basmala
 * @brief 
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include "functional"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"

using namespace std;
using SD_data = ara::com::proxy_skeleton::SD_data;
namespace ara 
{
namespace sm 
{
namespace update_request
{
namespace proxy
{
namespace events
{

}
namespace fields
{

}
namespace methods
{
    // using ResetMachine = int;
    // using StopUpdateSession = int;
    // using StartUpdateSession = int;
    // using PrepareUpdate = int;
    // using VerifyUpdate = int;
    // using PrepareRollback = int;
}



// struct C_Info
// {
//     int process_id;
//     char method_name[30];
//     int param1;
//     int param2;
// };


class update_request_proxy
{
    private:
    /* data */
    int portNumber;
    int service_id;
    int service_descovery_port_number;
    CServer s1;
    struct sockaddr_in  cliaddr;
    
    public:
    update_request_proxy(
       /* ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent*/
    );
    

        //Events
	
        //Fields

	
        //Methods
       virtual int ResetMachine();
       virtual int StopUpdateSession();
       virtual int StartUpdateSession();
       virtual int PrepareUpdate();
       virtual int VerifyUpdate();
       virtual int PrepareRollback();

        // init
       // init();
    

    
};
}
}
}
}