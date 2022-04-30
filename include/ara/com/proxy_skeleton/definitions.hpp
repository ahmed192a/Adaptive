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
                uint32_t service_id;
                int process_id;
                uint32_t port_number;
                bool message_type;
                bool operator==(SD_data &other)
                {
                    if (service_id == other.service_id && process_id == other.process_id && port_number == other.port_number && message_type == other.message_type)
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

                /**
                 * 0 ->new value
                 * 1 ->subscripe
                 * 2 ->unsubscripe
                 * 3 ->set
                 * 4 ->get
                 */
                uint32_t data_size;
                uint8_t operation;

                // std::vector<uint8_t> data;
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
                int port;
                std::string addr;
                bool operator==(const Client_udp_Info &kl)
                {
                    if (port == kl.port && addr == kl.addr)
                        return true;
                    return false;
                }
            };

        } // namespace proxy_skeleton
    }     // namespace com
} // namespace ara

#endif // ARA_COM_PROXY_SKELETON_DEFINITIONS_H_
