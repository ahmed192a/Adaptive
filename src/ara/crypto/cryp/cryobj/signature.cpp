#include <iostream>
#include<vector>
#include "ara/crypto/cryp/cryobj/sign.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            Sign::Sign(std::vector<uint8_t> signature)
            {
                this->signatureVal=signature;
                this->session =true;
                this->exportable =true;
            }
            CryptoPrimitiveId::AlgId Sign:: GetHashAlgId () const noexcept
            {
                return this->H_SingID ;
            }
            std::size_t Sign:: GetRequiredHashSize () const noexcept
            {
                return this->H_Req_Size;
            }

           // bool Sign::IsExportable () const noexcept
            //{
              //  return this->Export;
            //}
                
              //  bool Sign::IsSession () const noexcept
               // {
                 //   return this->Session;
                //}
                //CryptoObject::COIdentifier Sign::GetObjectId() const noexcept
                //{
                 //   return this->ID;
                //}
        }
    }
}
