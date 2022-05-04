#include "ara/crypto/cryp/cryobj/crypto_obj.hpp"
#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            class ConcreteCryptoProvider;
            class CryptoContext;
            /**template <class ConcreteObject> static ara::core::Result<typename ConcreteObject::Uptrc> cryptoobj:: Downcast(CryptoObject::Uptrc &&object) noexcept
            {
                ara::core::Result<typename ConcreteObject::Uptrc> & op =  && object ;
                return op;
            }**/
            CryptoPrId::Uptr cryptoobj:: GetCryptoPrimitiveId () const noexcept
            {
               return std::unique_ptr<CryptoPrId>();
            }
            CryptoObject::COIdentifier cryptoobj::GetObjectId ()  const noexcept
            {
               return this->CO_ID;
            }
            std::size_t CryptoObject:: GetPayloadSize () const noexcept
            {
                ConcreteCryptoProvider *CRY_PR;
                CryptoContext *CRY_CO;
                CryptoPrimitiveId *CRY_ID;
                CryptoPrimitiveId::AlgId PR_ID = CRY_ID->GetPrimitiveId();
                return CRY_CO->MyProvider().GetPayloadStorageSize(CO_ID.mCOType,PR_ID).Value(); 
                
            }//// related to crypto provider
            bool cryptoobj:: IsExportable () const noexcept
            {
                if(this->CO_ID.mCOType == ara::crypto::CryptoObjectType::kUndefined 
                && this->CO_ID.mCouid.mGeneratorUid.mQwordLs == 0u && this->CO_ID.mCouid.mGeneratorUid.mQwordMs == 0u )
                return false;
                else
                return true;
            }
            bool cryptoobj::IsSession () const noexcept
            {
                if(this->IsExportable())
                return false;
                else
                return true;
            }
            /*ara::core::Result<void> CryptoObject::Save (IOInterface &container) const noexcept
            {
               container.GetAllowedUsage();
               
            }*/////To Do after io-interface be done.
          
            cryptoobj& cryptoobj::operator= (const cryptoobj &other)
            {
                if(this != &other)
                {
                    CO_ID.mCouid = other.CO_ID.mCouid;
                    CO_ID.mCOType = other.CO_ID.mCOType;
                }
                return *this ;
            }
            cryptoobj& cryptoobj::operator= (cryptoobj &&other)
            {
                if(this != &other)
                {
                    CO_ID.mCouid = other.CO_ID.mCouid;
                    CO_ID.mCOType = other.CO_ID.mCOType;
                }
                return *this ;
            }
            
        }
    }
}
