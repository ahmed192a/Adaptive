#include "ara/crypto/keys/Inher_key_slote.hpp"

#include <iostream>
namespace ara
{ 
    namespace crypto
    {
        namespace keys
        {
        //Check the slot for emptiness//
        bool keys::IsEmpty() noexcept 
        {
            if (Empty_State)
            {
                return true;//true if the slot is empty or false otherwise//
            }
            else
                return false;
        }
            
        /*Save the content of a provided source IOInterface to this key - slot*/
        void keys::SaveCopy(const IOInterface& container) noexcept
        { 
            if(!(IOInterface_State_Empty))//if the source IOInterface isn't empty//
                {
            //Key Slot Content Properties Struct variables //
           KSCP.mAlgId = container.GetPrimitiveId();
           KSCP.mObjectType = container.GetCryptoObjectType();
           KSCP.mObjectUid = container.GetObjectId();
           KSCP.mContentAllowedUsage = container.GetAllowedUsage();
           KSCP.mObjectSize = container.GetCapacity();//shall return capacity of the underlying resource in bytes//
           //Key Slot Prototypes Struct variables//
           KSPP.mSlotCapacity= container.GetCapacity();//shall return capacity of the underlying resource in bytes//
           KSPP.mSlotType = container.Slot_Type;
           KSPP.mAlgId = container.GetPrimitiveId();
           KSPP.mAllocateSpareSlot = container.AllocateSpareSlot_t;
           KSPP.mAllowContentTypeChange = container.AllowContentTypeChange_t;
           KSPP.mMaxUpdateAllowed = container.MaxUpdateAllowed_t;
           KSPP.mExportAllowed=container.ExportAllowed_t;
           KSPP.mContentAllowedUsage=container.GetAllowedUsage();
           KSPP.mObjectType = container.GetTypeRestriction();
           //change state of key slot to committed //
           this->state = SlotState::committed;
           Empty_State=false;
      
               }
        
        }
        //Open this key slot and return an IOInterface to its content//
        IOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false)
        {

           //instance of IOInterface//
            IOInterface::Uptr IOContent = std::make_unique<IOInterface>;
            //Key Slot Content Properties Struct variables //
            IOContent.GetPrimitiveId() = KSCP.mAlgId;
            IOContent.GetCryptoObjectType() = KSCP.mObjectType;
            IOContent.GetObjectId() = KSCP.mObjectUid;
            IOContent.GetAllowedUsage() = KSCP.mContentAllowedUsage;
            IOContent.GetCapacity() = KSCP.mObjectSize;
            //Key Slot Prototypes Struct variables//
            IOContent.GetCapacity() = KSPP.mSlotCapacity;
            IOContent.Slot_Type = KSPP.mSlotType;
            IOContent.GetPrimitiveId() = KSPP.mAlgId;
            IOContent.AllocateSpareSlot_t = KSPP.mAllocateSpareSlot;
            IOContent.AllowContentTypeChange_t = KSPP.mAllowContentTypeChange;
            IOContent.MaxUpdateAllowed_t = KSPP.mMaxUpdateAllowed;
            IOContent.ExportAllowed_t = KSPP.mExportAllowed;
            IOContent.GetAllowedUsage() = KSPP.mContentAllowedUsage;
            IOContent.GetTypeRestriction() = KSPP.mObjectType;
            //change state of key slot to opened //
            this->state = SlotState::opened;
            return IOContent;

        
        }
            
            
            
            
           
            KeySlotPrototypeProps InhKeySlot :: GetPrototypedProps ()const noexcept
            {
                return KSPP;
            }
            
            KeySlot& InhKeySlot ::operator= (const KeySlot &other)
            {
                if(this != &other)
                {
                    this->KSCP.mAlgId = other.KSCP.mAlgId;
                    this->KSCP.mContentAllowedUsage = other.KSCP.mContentAllowedUsage;
                    this->KSCP.mObjectSize = other.KSCP.mObjectSize;
                    this->KSCP.mObjectUid.mGeneratorUid.mQwordLs=other.KSCP.mObjectUid.mGeneratorUid.mQwordLs;
                    this->KSCP.mObjectUid.mGeneratorUid.mQwordMs=other.KSCP.mObjectUid.mGeneratorUid.mQwordMs;
                    this->KSCP.mObjectUid.mVersionStamp=other.KSCP.mObjectUid.mVersionStamp;
                    this->KSCP.mObjectType =other.KSCP.mObjectType;
                    this->Myprov ;

                    this->KSPP.mAlgId = other.KSPP.mAlgId ;
                    this->KSPP.mAllocateSpareSlot = other.KSPP.mAllocateSpareSlot ;
                    this->KSPP.mAllowContentTypeChange = other.KSPP.mAllowContentTypeChange ;
                    this->KSPP.mContentAllowedUsage = other.KSPP.mContentAllowedUsage ;
                    this->KSPP.mExportAllowed = other.KSPP.mExportAllowed ;
                    this->KSPP.mMaxUpdateAllowed = other.KSPP.mMaxUpdateAllowed ;
                    this->KSPP.mObjectType = other.KSPP.mObjectType ;
                    this->KSPP.mSlotCapacity = other.KSPP.mSlotCapacity ;
                    this->KSPP.mSlotType = other.KSPP.mSlotType;
                    
                }
                return *this;
            }
            KeySlot& InhKeySlot ::operator= (KeySlot &&other)
            {
                if(this != &other)
                {
                    this->KSCP.mAlgId = other.KSCP.mAlgId;
                    this->KSCP.mContentAllowedUsage = other.KSCP.mContentAllowedUsage;
                    this->KSCP.mObjectSize = other.KSCP.mObjectSize;
                    this->KSCP.mObjectUid.mGeneratorUid.mQwordLs=other.KSCP.mObjectUid.mGeneratorUid.mQwordLs;
                    this->KSCP.mObjectUid.mGeneratorUid.mQwordMs=other.KSCP.mObjectUid.mGeneratorUid.mQwordMs;
                    this->KSCP.mObjectUid.mVersionStamp=other.KSCP.mObjectUid.mVersionStamp;
                    this->KSCP.mObjectType =other.KSCP.mObjectType;
                    this->Myprov ;

                    this->KSPP.mAlgId = other.KSPP.mAlgId ;
                    this->KSPP.mAllocateSpareSlot = other.KSPP.mAllocateSpareSlot ;
                    this->KSPP.mAllowContentTypeChange = other.KSPP.mAllowContentTypeChange ;
                    this->KSPP.mContentAllowedUsage = other.KSPP.mContentAllowedUsage ;
                    this->KSPP.mExportAllowed = other.KSPP.mExportAllowed ;
                    this->KSPP.mMaxUpdateAllowed = other.KSPP.mMaxUpdateAllowed ;
                    this->KSPP.mObjectType = other.KSPP.mObjectType ;
                    this->KSPP.mSlotCapacity = other.KSPP.mSlotCapacity ;
                    this->KSPP.mSlotType = other.KSPP.mSlotType;
                    
                }
                return *this;
            }
               KeySlotContentProps InhKeySlot :: GetContentProps () const noexcept
                 {
                   //Return the key slot content properties 
                     return KSCP;
                  }
    
                cryp::CryptoProvider::Uptr InhKeySlot ::MyProvider ()const noexcept
                  {
                  // return a pointer to the related CryptoProvider.
                 return Myprov;
                   }
    
                 void InhKeySlot :: Clear () noexcept
                  {
                     // Clear all the content of the key slot.
                      KSCP.mAlgId = 0;
                      KSCP.mContentAllowedUsage = 0;
                      KSCP.mObjectSize = 0;
                      KSCP.mObjectUid.mGeneratorUid.mQwordLs=0;
                      KSCP.mObjectUid.mGeneratorUid.mQwordMs=0;
                      KSCP.mObjectUid.mVersionStamp=0;
                      KSCP.mObjectType =ara::crypto::CryptoObjectType::kUndefined;
                      Myprov =nullptr;
                   }
 
        }
    }
}
