#include "ara/crypto/cryp/cryobj/crypto_pr_id.hpp"
#include <iostream>

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {    
            int CryptoPrId::ConvertToAlgId (std::string primitiveName)
            {
                //check the list of algorithm names supported
                for(int i=0;i<ALGORITHMSNUMBER;i++)
                {
                    if(primitiveName==algorithmNames[i])
                        return i+1;
                }
                //if not found so return undefined
                return kAlgIdUndefined;
            }
           
            CryptoPrId:: CryptoPrId(const std::string Sv) : name (Sv)
            {
                int cp = CryptoPrId::ConvertToAlgId (Sv);
                id = cp ;
            } 

            CryptoPrId:: AlgId CryptoPrId:: GetPrimitiveId () const noexcept
            {
               return id;
            }
            const std::string CryptoPrId:: GetPrimitiveName () const noexcept
            {
               return name ;
            }
            // return a referance to it self
            CryptoPrimitiveId& CryptoPrId:: operator= (const CryptoPrId &other)//assignment operator or copy operator
            {
               if(this != &other)
                {
                  id = other.id;
                  name = other.name;
                }
                return *this;
            }
            CryptoPrimitiveId& CryptoPrId:: operator= (CryptoPrId &&other)
            {
                if(this != &other)
                {
                  id = other.id;
                  name = other.name;
                }
               return *this;
            }
        }
    }
}
        
