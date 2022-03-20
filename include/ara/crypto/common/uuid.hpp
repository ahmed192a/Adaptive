#ifndef ARA_CRYPTO_UUID_H
#define ARA_CRYPTO_UUID_H

namespace ara
{
	namespace crypto
	{
        //SWS_CRYPT_10400
        
        /**
        * @brief Definition of Universally Unique Identifier (UUID) type. Independently from internal definition 
        * details of this structure, it’s size must be 16 bytes and entropy of this ID should be close to 128 bit
        **/
    
         struct Uuid
         {
            std::uint64_t mQwordLs = 0u;
            std::uint64_t mQwordMs = 0u;
          };

    }
}

#endif




