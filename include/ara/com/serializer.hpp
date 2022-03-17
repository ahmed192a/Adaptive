/**
 * @file serializer.hpp
 * @author your name (you@domain.com)
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
        class Serializer
        {
        private:
            std::vector<uint8_t> payload;

        public:
            Serializer() {}
            ~Serializer() {}
            template <typename T>
            void serialize(T data)
            {
                std::vector<uint8_t> buffer(sizeof(data));
                memcpy(&buffer[0], (const void *)&data, sizeof(data));
                payload.insert(payload.end(), buffer.begin(), buffer.end());
            }
            void Clear()
            {
                payload.clear();
            }
            std::vector<uint8_t> Payload()
            {
                return payload;
            }
        };
    } // com
} // ara

#endif // ARA_COM_SERIALIZER_H_
