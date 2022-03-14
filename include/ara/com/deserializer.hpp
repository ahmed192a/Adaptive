/**
 * @file deserializer.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_DESERIALIZER_H_
#define ARA_COM_DESERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <string.h>
#include <map>

namespace ara
{
    namespace com
    {
        class Deserializer
        {
        public:
            Deserializer() {}
            ~Deserializer() {}
            template <typename T>
            T deserialize(std::vector<uint8_t> data, int ind)
            {
                
                T result;

                memcpy(&result, (const void *)&data[ind], sizeof(result));
                return result;
            }
        };

    } // com
} // ara

#endif // ARA_COM_DESERIALIZER_H_
