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

            // Definition of service version type
            using ServiceVersion = std::uint32_t;

            // Definition of proxy_skeleton instance ID type that should be binding agnostic.
            using InstanceId = std::uint16_t;

            // Definition of proxy_skeleton service ID type that should be binding agnostic.
            using ServiceId = std::uint16_t;

            // "Null" instance ID
            static const InstanceId INSTANCE_ID_UNKNOWN = 0xFFFF;

            struct Message
            {
                int process_id;
                char method_name[30];
                std::vector<uint8_t> payload;
            };

            struct C_Info
            {
                int process_id;
                char method_name[30];
                int param1;
                int param2;
            };
            struct SD_data
            {
                int service_id;
                int process_id;
                int port_number;
                bool message_type;
            };
            struct event_info{
                int process_id;
                char event_name[30];
                int event_id;
                int service_id;
            };

        } // namespace proxy_skeleton
    } // namespace com
} // namespace ara

#endif // ARA_COM_PROXY_SKELETON_DEFINITIONS_H_
