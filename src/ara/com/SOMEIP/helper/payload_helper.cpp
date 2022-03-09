/**
 * @file payload_helper.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/helper/payload_helper.hpp"
#include <cstring>
namespace ara
{
    namespace com
    {
        namespace helper
        {
            void Inject(std::vector<uint8_t> &vector, uint16_t value)
            {
                uint8_t _byte;

                _byte = value >> 8;
                vector.push_back(_byte);

                _byte = value;
                vector.push_back(_byte);
            }

            void Inject(std::vector<uint8_t> &vector, uint32_t value)
            {
                uint8_t _byte;

                _byte = value >> 24;
                vector.push_back(_byte);

                _byte = value >> 16;
                vector.push_back(_byte);

                _byte = value >> 8;
                vector.push_back(_byte);

                _byte = value;
                vector.push_back(_byte);
            }
            template <typename T>
            void Inject(std::vector<uint8_t> &vector, T data)
            {
                std::vector<uint8_t> buffer(sizeof(data));
                memcpy(&buffer[0], (const void *)&data, sizeof(data));
                vector.insert(vector.end(), buffer.begin(), buffer.end());
            }

            void Concat(std::vector<uint8_t> &vector1, std::vector<uint8_t> &&vector2)
            {
                vector1.insert(vector1.end(), vector2.begin(), vector2.end());
            }
        }
    }
}