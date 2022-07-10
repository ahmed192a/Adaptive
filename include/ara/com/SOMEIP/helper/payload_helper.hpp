/**
 * @file payload_helper.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PAYLOAD_HELPER_H
#define PAYLOAD_HELPER_H

#include <vector>
#include <stdint.h>
#include <cstring>
namespace ara
{
    namespace com
    {
        /// @brief Helper functions required for communication classes
        /// @note The namespace is not part of the official AUTOSAR standard.
        namespace helper
        {
            /// @brief Inject a short value into a byte vector
            /// @param vector Byte vector
            /// @param value Short input value
            void Inject(std::vector<uint8_t> &vector, uint16_t value);

            /// @brief Inject an integer value into a byte vector
            /// @param vector Byte vector
            /// @param value Integer input value
            void Inject(std::vector<uint8_t> &vector, uint32_t value);


            template <typename T>
            void Inject(std::vector<uint8_t> &vector, T data);

            /// @brief Concat the second vector into the end of the first vector
            /// @param vector1 First vector
            /// @param vector2 Second vector
            void Concat(std::vector<uint8_t> &vector1, std::vector<uint8_t> &&vector2);

            template <typename T>
            T Extract (const std::vector<uint8_t> &vector, size_t offset)
            {
                T result;
                memcpy(&result, &vector[offset], sizeof(T));
                return result;
            }

            std::vector<uint8_t> Extracts(const std::vector<uint8_t> &vector, size_t offset, size_t length);
            
        }
    }
}
#endif