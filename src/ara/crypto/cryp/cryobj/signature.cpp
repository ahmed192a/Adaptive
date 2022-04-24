#include <iostream>
#include "ara/crypto/cryp/cryobj/sign.hpp"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            CryptoPrimitiveId::AlgId Sign:: GetHashAlgId () const
            {
                return this->H_SingID ;
            }
            std::size_t Sign:: GetRequiredHashSize () const 
            {
                return this->H_Req_Size;
            }
        }
    }
}
