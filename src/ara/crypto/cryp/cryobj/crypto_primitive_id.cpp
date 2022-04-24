#include "ara/crypto/cryp/cryobj/crypto_pr_id.hpp"
#include <iostream>

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {    
            
            CryptoPrId:: CryptoPrId(const std::string &Sv) : name(Sv)
            {
                ConcreteCryptoProvider *CC_PRO;
                CryptoProvider :: AlgId cp = CC_PRO->ConvertToAlgId (Sv);
                id = cp ;
            } 

            CryptoPrId:: AlgId CryptoPrId:: GetPrimitiveId () const
            {
                return id;
            }
            const std::string CryptoPrId:: GetPrimitiveName () const
            {
                return name ;
            }
            //return a referance to it self
            CryptoPrimitiveId& CryptoPrId:: operator= (const CryptoPrimitiveId &other)//assignment operator or copy operator
            {
                if(this != &other)
                {
                   id = other.GetPrimitiveId();
                   //name = other.GetPrimitiveName();
                }
                return *this;
            }
            CryptoPrimitiveId& CryptoPrId:: operator= (CryptoPrimitiveId &&other)
            {
                 if(this != &other)
                {
                   id = other.GetPrimitiveId();
                  // name = other.GetPrimitiveName ();
                }
                return *this;
            }
        }
    }
}
        

