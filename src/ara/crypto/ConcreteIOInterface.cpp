#include "../../../include/ara/crypto/common/concrete_io_interface.hpp"

using namespace ara::crypto;

                ConcreteIOInterface::ConcreteIOInterface(ara::crypto::KeySlotType Slot_Typevar,std::int32_t MaxUpdateAllowedvar,bool  IOInterface_State_Emptyvar, bool AllocateSpareSlotvar,bool AllowContentTypeChangevar,bool ExportAllowvar,bool Volatilevar ,bool sessionvar,AllowedUsageFlags AllowedUsagevar,CryptoObjectType objectTypevar/*kSymmetricKey*/,CryptoObjectUid objectIdvar,std::size_t capacityvar,std::size_t payloadSizevar,CryptoAlgId algidvar,CryptoObjectType objectTypeRestictionvar)
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
	    ExportAllowed_t = ExportAllowvar;
            AllowContentTypeChange_t = AllowContentTypeChangevar;
            AllocateSpareSlot_t = AllocateSpareSlotvar;
            IOInterface_State_Empty = IOInterface_State_Emptyvar;
            MaxUpdateAllowed_t = MaxUpdateAllowedvar;
            Slot_Type = Slot_Typevar;

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
                 bool ConcreteIOInterface::IsExportAllowed() const noexcept 
                 {
                     return this->ExportAllowed_t;
                 
                 }
                 bool ConcreteIOInterface::IsAllowContentTypeChange() const noexcept
                 {
                 
                     return this->AllowContentTypeChange_t;
                 }
                 bool ConcreteIOInterface::IsAllocateSpareSlot() const noexcept
                 {
                     return this->AllocateSpareSlot_t;
                 
                 }
                 bool  ConcreteIOInterface::IsIOInterface_State_Empty() const noexcept
                 {
                     return this->IOInterface_State_Empty;
                 }
                 std::int32_t ConcreteIOInterface::GetMaxUpdateAllowed() const noexcept
                 {
                 
                     return this->MaxUpdateAllowed_t; 
                 
                 }
                 KeySlotType ConcreteIOInterface::GetSlotType() const noexcept 
                 {
                     return this->Slot_Type;
                 }


				 //ConcreteIOInterface::~ConcreteIOInterface () noexcept
                 //{
                     
                 //}

