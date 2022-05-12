#ifndef ARA_CRYPTO_MEM_REGION_H
#define ARA_CRYPTO_MEM_REGION_H

#include <iostream>
#include <vector>
//#include <ara/core/span.hpp>
namespace ara
{
	namespace crypto
	{
        //SWS_CRYPT_10033
        /**
         * @brief Read-Only Memory Region (intended for [in] arguments)
         * 
         */
        using ReadOnlyMemRegion = std::vector<std::uint8_t>;
        //SWS_CRYPT_10031
        /**
         * @brief Read-Write Memory Region (intended for [in/out] arguments)
         * 
         */
        using ReadWriteMemRegion = std::vector<std::uint8_t>;

  
  }
}

#endif

