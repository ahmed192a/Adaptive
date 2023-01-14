/**
 * @file deserializer.hpp
 * @author Flashing Adapter Graduation Project Team
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
        /**
         * @brief Deserializer class for deserializing data
         */
        class Deserializer
        {
        public:
            /**
             * @brief Construct a new Deserializer object
             * 
             */
            Deserializer() {}
            /**
             * @brief Destroy the Deserializer object
             * 
             */
            ~Deserializer() {}
            /**
             * @brief Deserialize the vector of bytes into the required data type
             * 
             * @tparam T    Data type to be deserialized
             * @param data  Vector of bytes to be deserialized
             * @param ind   Index of the vector of bytes to be deserialized
             * @return T    Data tyoe of Deserialized and returned data
             */
            template <typename T>
            T deserialize(std::vector<uint8_t> data, int ind)
            {
                T result;                              // Variable to store the deserialized data
                memcpy(&result, (const void *)&data[ind], sizeof(result));  // Copy the data from the vector of bytes to the variable
                                                                            // of the required data type
                return result;                          // Return the deserialized data
            }
        };

    } // com
} // ara

#endif // ARA_COM_DESERIALIZER_H_
