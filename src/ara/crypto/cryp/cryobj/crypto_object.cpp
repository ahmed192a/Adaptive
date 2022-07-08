#include"../../../../../include/ara/crypto/common/concrete_io_interface.hpp"
#include "../../../../../include/ara/crypto/cryp/cryobj/crypto_obj.hpp"
#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            cryptoobj::cryptoobj(std::size_t payloadSize , bool session,bool exportable,CryptoObjectType object_type)
            {
                payloadSize = payloadSize;
                session = session;
                exportable = exportable;
                CO_ID.mCOType= object_type;
            }
            
           /** template <class ConcreteObject> typename ConcreteObject::Uptrc cryptoobj:: Downcast(CryptoObject::Uptrc &&object) noexcept
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
            std::size_t cryptoobj::GetPayloadSize () const noexcept
            {
                
                return this->payloadSize;
                
            }
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
            
            void cryptoobj::Save (ConcreteIOInterface &container) const noexcept
            {
                // A CryptoObject with property "session" cannot be saved in a KeySlot.
                if(!(this->session))
                {
                 container->payloadSize = this->payloadSize;
                 container->objectType = this->CO_ID.mCOType;
                 container->objectId.mGeneratorUid.mQwordLs = this->CO_ID.mCouid.mGeneratorUid.mQwordLs;
                 container->objectId.mGeneratorUid.mQwordMs = this->CO_ID.mCouid.mGeneratorUid.mQwordMs;
                 container->objectId.mVersionStamp = this->CO_ID.mCouid.mVersionStamp;
                 container->AllowedUsage =this->Allow_U;
                 container->session =this->session;
                }
             }            
       
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
