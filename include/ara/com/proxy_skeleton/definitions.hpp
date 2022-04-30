/**
 * @file definitions.hpp
 * @author
 * @brief
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_PROXY_SKELETON_DEFINITIONS_H_
#define ARA_COM_PROXY_SKELETON_DEFINITIONS_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {

            using ServiceVersion = std::uint32_t;       //!< Definition of service version type

            using InstanceId = std::uint16_t;       //!< Definition of proxy_skeleton instance ID type.

            using ServiceId = std::uint16_t;        //!< Definition of proxy_skeleton service ID type. 

            static const InstanceId INSTANCE_ID_UNKNOWN = 0xFFFF;   //!< Definition of Unkown (NULL) instance ID type.



            struct SD_data
            {
                uint16_t service_id;
                uint16_t instance_id;
                uint32_t port_number;
                bool operator==(SD_data &other)
                {
                    if (service_id == other.service_id && instance_id == other.instance_id && port_number == other.port_number)
                    {
                        return true;
                    }
                    return false;
                }
            };

            struct event_info
            {
                uint32_t service_id;
                uint32_t event_id;
            };
            template <typename T>
            struct event_notify
            {
                int event_id;
                int service_id;
                T newdata;
            };
            struct Client_udp_Info
            {
                uint32_t port;
                std::string addr;
                bool operator==(const Client_udp_Info &other)
                {
                    if (port == other.port && addr == other.addr)
                        return true;
                    return false;
                }
            };

        } // namespace proxy_skeleton
    }     // namespace com
} // namespace ara

#endif // ARA_COM_PROXY_SKELETON_DEFINITIONS_H_
