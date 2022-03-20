#ifndef ARA_CRYPTO_CRYPTOOBJECTUID_H
#define ARA_CRYPTO_CRYPTOOBJECTUID_H

#include "ara/crypto/common/uuid.h"

namespace ara
{
	namespace crypto
	{
        //SWS_CRYPT_10100
        /**
         * @brief Definition of Crypto Object Unique Identifier (COUID) type.
         * 
         */
        struct CryptoObjectUid
        {
		Uuid mGeneratorUid;
        };

    }
}
#endif
