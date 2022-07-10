/**
 * @file serializer.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_SERIALIZER_H_
#define ARA_COM_SERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstring>
#include <iostream>


namespace ara
{
    namespace com
    {
        /**
         * @brief Serializer class for serializing data
         * 
         */
        class Serializer
        {
        private:
            std::vector<uint8_t> payload;           //!< The payload of the serializer

        public:
            /**
             * @brief Construct a new Serializer object
             * 
             */
            Serializer() {}
            /**
             * @brief Destroy the Serializer object
             * 
             */
            ~Serializer() {}
            /**
             * @brief serialize the data into the vector of bytes
             * 
             * @tparam T 
             * @param data 
             */
            template <typename T>
            void serialize(T data)
            {
                std::vector<uint8_t> buffer(sizeof(data));
                memcpy(&buffer[0], (const void *)&data, sizeof(data));
                payload.insert(payload.end(), buffer.begin(), buffer.end());
            }
            /**
             * @brief Clear the payload of the serializer
             * 
             */
            void Clear()
            {
                payload.clear();
            }
            /**
             * @brief Get the Payload object of the serializer
             * 
             */
            std::vector<uint8_t> Payload()
            {
                return payload;
            }
        };
    } // com
} // ara

#endif // ARA_COM_SERIALIZER_H_
