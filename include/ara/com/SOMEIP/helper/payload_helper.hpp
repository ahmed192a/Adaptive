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


            /**
             * @brief Extract a variable of type T from a byte vector
             * 
             * @tparam T        Type of the variable to be extracted
             * @param vector    Byte vector
             * @param offset    Offset of the variable in the byte vector
             * @return T        Extracted variable
             */
            template <typename T>
            T Extract (const std::vector<uint8_t> &vector, size_t offset)
            {
                T result;
                memcpy(&result, &vector[offset], sizeof(T));
                return result;
            }

            /**
             * @brief Extract a short vector of bytes from alarge vector of bytes
             * 
             * @param vector        Byte vector
             * @param offset        Offset of the short value in the byte vector
             * @param length        Length of the short vector of bytes
             * @return std::vector<uint8_t>     Short vector of bytes
             */
            std::vector<uint8_t> Extracts(const std::vector<uint8_t> &vector, size_t offset, size_t length);
            
        }
    }
}
#endif