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
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"
#include "ara/com/SOMEIP/option/option.hpp"
#include "ara/com/serializer.hpp"
#include "ara/com/deserializer.hpp"
#include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
#include "ara/com/SOMEIP/entry/entry.hpp"
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
                ServiceHandleContainer<ServiceProxy::SP_Handle> ServiceProxy::FindService(FindServiceHandle FSH)
                {
                    ServiceHandleContainer<ServiceProxy::SP_Handle> vhandler;
                    // vhandler.resize(1);
                    // Send a service id to the service discovery
                    // receive a struct
                    //m_service_id = service_id;
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

                    SOMEIP_MESSAGE::sd::SomeIpSDMessage m_info;
                    SOMEIP_MESSAGE::sd::SomeIpSDMessage msg_info;
                    entry::ServiceEntry event_gr_entry = entry::ServiceEntry::CreateFindServiceEntry (static_cast<uint16_t>(FSH.service_id));
                    
                    m_info.AddEntry(&event_gr_entry);
                    std::vector<uint8_t> _payload = m_info.Serializer();
                    uint32_t _payload_size = _payload.size();

                    Client_SD.GetHost("127.0.0.1", FSH.uid);
                    Client_SD.ClientConnect();

                    // send the service id
                    Client_SD.ClientWrite(&_payload_size, sizeof(_payload_size));
                    Client_SD.ClientWrite(_payload.data(), _payload_size);
                    _payload.clear();
                    // receive a struct
                    Client_SD.ClientRead(&_payload_size, sizeof(_payload_size));
                    _payload.resize(_payload_size);
                    Client_SD.ClientRead(_payload.data(), _payload_size);
                    std::cout<<"Find SEERIVEC _payload_size : "<<_payload_size<<"\n";
                    msg_info.Deserialize(_payload);
                    
                    Client_SD.CloseSocket();

                    auto entry = msg_info.Entries()[0];  
                    auto options = entry->FirstOptions();
                    
                    for (auto option : options)
                    {
                        ServiceProxy::SP_Handle handle;
                        //service_id in  haandle
                        //sp_handle -> service_id, instance_id<->process_id, port_id,  
                        option::Ipv4EndpointOption *ipv4_endpoint = dynamic_cast<option::Ipv4EndpointOption *>(option);

                        handle.m_server_com.port_number = ipv4_endpoint->Port();
                        handle.m_server_com.service_id = FSH.service_id;
                        handle.m_server_com.process_id = FSH.instance_id;
                        vhandler.push_back(handle);
                    }
                    return vhandler;
                }

                

                ServiceProxy::ServiceProxy(SP_Handle proxy_handle)
                :m_proxy_handle{proxy_handle},
                service_proxy_tcp(SOCK_STREAM),
                service_proxy_udp(SOCK_DGRAM)
                {
                    // service_proxy_udp.OpenSocket();
                    //m_proxy_handle.m_client_UPD = &service_proxy_udp;
                }
                ServiceProxy::~ServiceProxy()
                {
                }

            }
        }
    }
}
