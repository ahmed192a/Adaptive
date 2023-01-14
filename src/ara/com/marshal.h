/**
 * @file marshal.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_MARSHAL_H_
#define ARA_COM_MARSHAL_H_

#include "ara/com/deserializer.h"
#include <iostream>

namespace ara
{
    namespace com
    {
        /**
         * @brief if it's not the last argument of the function, 
         *         then decrement the argument counter I and send the Tail which is the rest of the arguments.
         *          until it's  I = 0. then return The Head which is the type of the Argument.
         * 
         * @tparam I          number remaining of the arguments  
         * @tparam Head       type of the argument to be sent to the function (the first argument)
         * @tparam Tail       type of the rest of the arguments to be sent to the function (the rest of the arguments)
         */
        template <std::size_t I, typename Head, typename... Tail>
        struct ArgumentTypeImpl
        {
            using type = typename ArgumentTypeImpl<I - 1, Tail...>::type;   // get the type of the the argument
        };
        /**
         * @brief if it's the last argument of the function, then return the head which is the type of the argument.
         * 
         * @tparam Head     type of the argument to be sent to the function (the first argument)
         * @tparam Tail     type of the rest of the arguments to be sent to the function (the rest of the arguments)
         */
        template <typename Head, typename... Tail>
        struct ArgumentTypeImpl<0, Head, Tail...>
        {
            using type = Head;                                // get the type of the the argument
        };

        template <std::size_t I, typename... Args>
        using ArgumentType = typename ArgumentTypeImpl<I, Args...>::type;   // get the type of the the argument

        /**
         * @struct MessageIndexerImpl
         * @brief MessageIndexerImpl is a helper struct for the Marshal class to get the index of each argument in the vector of bytes.
         * 
         * @tparam I        number remaining of the arguments
         * @tparam Args     type of the rest of the arguments to be sent to the function (the rest of the arguments)
         */
        template <std::size_t I, typename... Args>
        struct MessageIndexerImpl
        {
            /**
             * @brief operator() is a function that calculates the index of each argument in the vector of bytes.
             * 
             * @param v 
             */
            void operator()(std::vector<uint32_t> &v)
            {

                MessageIndexerImpl<I - 1, Args...> next;
                next(v);

                typename std::decay<ArgumentType<I, Args...>>::type k;
                v.push_back(sizeof(k));
            }
        };

        /**
         * @struct MessageIndexerImpl
         * @brief MessageIndexerImpl An overload of the MessageIndexerImpl struct for the last argument of the function.
         * 
         * @tparam Args     type of the rest of the arguments to be sent to the function (the rest of the arguments)
         */
        template <typename... Args>
        struct MessageIndexerImpl<0, Args...>
        {
            /**
             * @brief operator() is a function that calculates the index of each argument in the vector of bytes.
             * 
             * @param v 
             */
            void operator()(std::vector<uint32_t> &v)
            {
                typename std::decay<ArgumentType<0, Args...>>::type k;
                v.push_back(sizeof(k));
                // std::cout << "sizes\n";
                // std::cout << v.back() << std::endl;
            }
        };

        /**
         * @brief marshal class for deserializing vector of data bytes to the required parameters from Args
         * 
         * @tparam Args 
         */
        template <typename... Args>
        class Marshal                   
        {
        private:
            Deserializer mdes;              //!< Deserializer object
            std::vector<uint8_t> mv;        //!< Vector of data bytes
            std::vector<uint32_t> sizes;    //!< Vector of sizes of each data type

        public:
            /**
             * @brief Construct a new Marshal object
             * 
             * @param v  vector of data bytes
             */
            Marshal(std::vector<uint8_t> v) : mv{v}
            {
                sizes.push_back(0);
                MessageIndexerImpl<sizeof...(Args) - 1, Args...> mindex;
                mindex(sizes);
            }
            
            /**
             * @brief unmarshal the data bytes into the required parameters
             * 
             * @tparam I                                            Index of the parameter
             * @return std::decay<ArgumentType<I, Args...>>::type   The value of the parameter
             */
            template <std::size_t I>
            typename std::decay<ArgumentType<I, Args...>>::type unmarshal()
            {
                typename std::decay<ArgumentType<I, Args...>>::type kl;
                kl = mdes.deserialize<typename std::decay<ArgumentType<I, Args...>>::type>(mv, sizes[I]);
                return kl;
            }
        };
    } // com
} // ara

#endif // ARA_COM_MARSHAL_H_
