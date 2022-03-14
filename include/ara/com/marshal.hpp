/**
 * @file marshal.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_MARSHAL_H_
#define ARA_COM_MARSHAL_H_

#include "ara/com/deserializer.hpp"
#include <vector>
#include <iostream>

namespace ara
{
    namespace com
    {
        template <std::size_t I, typename Head, typename... Tail>
        struct ArgumentTypeImpl
        {
            using type = typename ArgumentTypeImpl<I - 1, Tail...>::type;
        };

        template <typename Head, typename... Tail>
        struct ArgumentTypeImpl<0, Head, Tail...>
        {
            using type = Head;
        };

        template <std::size_t I, typename... Args>
        using ArgumentType = typename ArgumentTypeImpl<I, Args...>::type;
        template <std::size_t I, typename... Args>
        struct MessageIndexerImpl
        {
            void operator()(std::vector<uint32_t> &v)
            {

                MessageIndexerImpl<I - 1, Args...> next;
                next(v);

                typename std::decay<ArgumentType<I, Args...>>::type k;
                v.push_back(sizeof(k));
                // std::cout << "sizes\n";
                // std::cout << v.back() << std::endl;
            }
        };
        template <typename... Args>
        struct MessageIndexerImpl<0, Args...>
        {
            void operator()(std::vector<uint32_t> &v)
            {
                typename std::decay<ArgumentType<0, Args...>>::type k;
                v.push_back(sizeof(k));
                // std::cout << "sizes\n";
                // std::cout << v.back() << std::endl;
            }
        };
        template <typename... Args>
        class Marshal
        {
        private:
            Deserializer mdes;
            std::vector<uint8_t> mv;
            std::vector<uint32_t> sizes;

        public:
            Marshal(std::vector<uint8_t> v) : mv{v}
            {
                sizes.push_back(0);
                MessageIndexerImpl<sizeof...(Args) - 1, Args...> mindex;
                mindex(sizes);
            }
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
