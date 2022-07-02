#include "../../../include/ara/crypto/common/concrete_io_interface.hpp"

using namespace ara::crypto;

                ConcreteIOInterface::ConcreteIOInterface(bool Volatilevar ,bool sessionvar,AllowedUsageFlags AllowedUsagevar,CryptoObjectType objectTypevar/*kSymmetricKey*/,CryptoObjectUid objectIdvar,std::size_t capacityvar,std::size_t payloadSizevar,CryptoAlgId algidvar,CryptoObjectType objectTypeRestictionvar)
        {
            Volatile=Volatilevar;
            session=sessionvar;
            AllowedUsage=AllowedUsagevar;
            objectType=objectTypevar;
            objectId=objectIdvar;
            capacity=capacityvar;
            payloadSize=payloadSizevar;
            algid=algidvar;
            objectTypeRestiction=objectTypeRestictionvar;
        }
         ConcreteIOInterface::ConcreteIOInterface()
         {

         }
        VolatileTrustedContainer::Uptr ConcreteIOInterface::CreateVolatileContainer(std::size_t capacity)
        {
            return std::make_unique<ConcreteVolatileTrustedContainer>(capacity, this);

        }
             AllowedUsageFlags ConcreteIOInterface::GetAllowedUsage () const noexcept
             {
                return this->AllowedUsage;
             }

				 std::size_t ConcreteIOInterface::GetCapacity () const noexcept
                 {
                    return this->capacity;
                 }

				 CryptoObjectType ConcreteIOInterface::GetCryptoObjectType () const noexcept
                 {
                     return this->objectType;
                 }

				 CryptoObjectUid ConcreteIOInterface::GetObjectId () const noexcept
                 {
                     return this->objectId;
                 }

				 std::size_t ConcreteIOInterface::GetPayloadSize () const noexcept
                 {
                     return this->payloadSize;
                 }

				 CryptoAlgId ConcreteIOInterface::GetPrimitiveId () const noexcept
                 {
                     return this->algid;
                 }

				 CryptoObjectType ConcreteIOInterface::GetTypeRestriction () const noexcept
                 {
                     return this->objectTypeRestiction;
                 }

				 bool ConcreteIOInterface::IsObjectSession () const noexcept
                 {
                     return this->session;
                 }

				 bool ConcreteIOInterface::IsVolatile () const noexcept
                 {
                     return this->Volatile;
                 }

				 //ConcreteIOInterface::~ConcreteIOInterface () noexcept
                 //{
                     
                 //}

