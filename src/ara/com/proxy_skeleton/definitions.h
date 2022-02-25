/**
 * @file definitions.h
 * @author
 * @brief
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_proxy_skeleton_DEFINITIONS_H_
#define ARA_COM_proxy_skeleton_DEFINITIONS_H_

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

        } // namespace proxy_skeleton
    } // namespace com
} // namespace ara

#endif // ARA_COM_proxy_skeleton_DEFINITIONS_H_
