#include "ara/crypto/keys/Inher_key_slote.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
namespace ara
{ 
    namespace crypto
    {
        namespace keys
        {
             InhKeySlot::InhKeySlot (std::string file_name)
            {
                std::string name = file_name;
                std::string path= "ara/crypto/keys/KeySlot/" + name + ".txt";//must write a complete file path 
                std::ofstream file(path); //open in constructor
                this->path = "ara/crypto/keys/KeySlot/" + name + ".txt";//must write a complete file path 
            }
            //Check the slot for emptiness//
            bool InhKeySlot::IsEmpty() noexcept 
            {
                if (Empty_State)
                {
                    return true;//true if the slot is empty or false otherwise//
                }
                else
                    return false;
            }
                
            /*Save the content of a provided source IOInterface to this key - slot*/
            void InhKeySlot::SaveCopy(const ConcreteIOInterface& container) noexcept
            { 
                if(!(container.IsIOInterface_State_Empty()))//if the source IOInterface isn't empty//
                {
                //Key Slot Content Properties Struct variables //
                    KSCP.mAlgId = container.GetPrimitiveId();
                    KSCP.mObjectType = container.GetCryptoObjectType();
                    KSCP.mObjectUid = container.GetObjectId();
                    KSCP.mContentAllowedUsage = container.GetAllowedUsage();
                    KSCP.mObjectSize = container.GetCapacity();//shall return capacity of the underlying resource in bytes//
                    //Key Slot Prototypes Struct variables//
                    KSPP.mSlotCapacity= container.GetCapacity();//shall return capacity of the underlying resource in bytes//
                    KSPP.mSlotType = container.GetSlotType();
                    KSPP.mAlgId = container.GetPrimitiveId();
                    //Elli etghyr//
                    KSPP.mAllocateSpareSlot = container.IsAllocateSpareSlot();
                    KSPP.mAllowContentTypeChange = container.IsAllowContentTypeChange();
                    KSPP.mMaxUpdateAllowed = container.GetMaxUpdateAllowed();
                    KSPP.mExportAllowed=container.IsExportAllowed();
                    KSPP.mContentAllowedUsage=container.GetAllowedUsage();
                    KSPP.mObjectType = container.GetTypeRestriction();
                    //change state of key slot to committed //
                    this->state = SlotState::commited;
                    Empty_State=false;
                
                }
            
            }
            //Open this key slot and return an IOInterface to its content//
            ConcreteIOInterface::Uptr InhKeySlot::Open(bool subscribeForUpdates = false, bool writeable = false)
            {

            //instance of IOInterface//
                ConcreteIOInterface::Uptr IOContent = std::make_unique<ConcreteIOInterface>;
                //Key Slot Content Properties Struct variables //
                IOContent->algid = KSCP.mAlgId;
                IOContent->objectType = KSCP.mObjectType;
                IOContent->objectId = KSCP.mObjectUid;
                IOContent->AllowedUsage = KSCP.mContentAllowedUsage;
                IOContent->capacity = KSCP.mObjectSize;
                //Key Slot Prototypes Struct variables//
                IOContent->capacity = KSPP.mSlotCapacity;
                IOContent->Slot_Type= KSPP.mSlotType;
                IOContent->algid = KSPP.mAlgId;
                IOContent->AllocateSpareSlot_t = KSPP.mAllocateSpareSlot;
                IOContent->AllowContentTypeChange_t= KSPP.mAllowContentTypeChange;
                IOContent->MaxUpdateAllowed_t = KSPP.mMaxUpdateAllowed;
                IOContent->ExportAllowed_t = KSPP.mExportAllowed;
                IOContent->AllowedUsage = KSPP.mContentAllowedUsage;
                IOContent->objectTypeRestiction = KSPP.mObjectType;
                //change state of key slot to opened //
                this->state = SlotState::opened;
                return IOContent;

            
            }
            KeySlotContentProps InhKeySlot :: GetContentProps () const noexcept
            {
                //KSPP->mExportAllowed=false;
                 return KSCP;
            }
            cryp::CryptoProvider::Uptr InhKeySlot ::MyProvider ()const noexcept
            {
                 return  std::unique_ptr<ara::crypto::cryp::CryptoProvider>();
            }
            KeySlotPrototypeProps InhKeySlot :: GetPrototypedProps ()const noexcept
            {
                return KSPP;
            }
            void InhKeySlot :: Clear () noexcept
            {
                KSCP.mAlgId = 0;
                KSCP.mContentAllowedUsage = 0;
                KSCP.mObjectSize = 0;
                KSCP.mObjectUid.mGeneratorUid.mQwordLs=0;
                KSCP.mObjectUid.mGeneratorUid.mQwordMs=0;
                KSCP.mObjectUid.mVersionStamp=0;
                KSCP.mObjectType =ara::crypto::CryptoObjectType::kUndefined;
                Myprov =nullptr;

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
        }
    }
}
