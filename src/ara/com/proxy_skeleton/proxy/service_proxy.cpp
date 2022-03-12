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
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include <iostream>
using C_Info = ara::com::proxy_skeleton::C_Info;


// struct C_Info
// {
//     int process_id;
//     char method_name[30];
//     int param1;
//     int param2;
// };

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace proxy
            {
                int ServiceProxy::FindService( int service_id)
                {
                    // Send a service id to the service discovery
                    // receive a struct
                    m_service_id = service_id;
                    char buffer[256];
                    char hostbuffer[256];
                    CClient Client_SD(SOCK_STREAM);
                    Client_SD.OpenSocket();
                    memset(hostbuffer,'\0', 256);
                    int hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

                    if (hostnameRet < 0)
                    {
                        std::cout << ("[SERVICE PROXY] ERROR : Unable to local machine get Host Name\n");
                    }

                    Client_SD.GetHost("127.0.0.1", m_proxy_handle->m_SD_PortNum);
                    Client_SD.ClientConnect();

                    // send the service id
                    Client_SD.ClientWrite(&service_id, sizeof(service_id));

                    // receive a struct
                    Client_SD.ClientRead(&this->server_handle, sizeof(server_handle));
                    Client_SD.CloseSocket();

                    
                    return 0;
                }

                

                ServiceProxy::ServiceProxy(SP_Handle * proxy_handle)
                :m_proxy_handle{proxy_handle},
                Cient_Server_connection(SOCK_STREAM)
                {
                }
                ServiceProxy::~ServiceProxy()
                {
                }

            }
        }
    }
}
