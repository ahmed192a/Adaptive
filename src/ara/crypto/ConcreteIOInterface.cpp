#include "../../../../include/ara/crypto/common/concrete_io_interface.hpp"

using namespace ara::crypto;

                ConcreteIOInterface::ConcreteIOInterface(bool Volatilevar=true ,bool sessionvar=true,AllowedUsageFlags AllowedUsagevar=0xFFFF,CryptoObjectType objectTypevar/*kSymmetricKey*/,CryptoObjectUid objectIdvar,std::size_t capacityvar=5,std::size_t payloadSizevar=0,CryptoAlgId algidvar=1,CryptoObjectType objectTypeRestictionvar)
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
        VolatileTrustedContainer::Uptr ConcreteIOInterface::CreateVolatileContainer(std::size_t capacity=0)
        {
            return std::make_unique<VolatileTrustedContainer>(capacity, this);

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




