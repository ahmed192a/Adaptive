#ifndef ARA_CRYPTO_CRYPTOOBJECTUID_H
#define ARA_CRYPTO_CRYPTOOBJECTUID_H

#include <iostream>
#include <ara/core/span.hpp>
namespace ara
{
	namespace crypto
	{
        //SWS_CRYPT_10033
        /**
         * @brief Read-Only Memory Region (intended for [in] arguments)
         * 
         */
        using ReadOnlyMemRegion = ara::core::Span<const std::uint8_t>;
        //SWS_CRYPT_10031
        /**
         * @brief Read-Write Memory Region (intended for [in/out] arguments)
         * 
         */
        using ReadWriteMemRegion = ara::core::Span<std::uint8_t>;

    }
}

#endif