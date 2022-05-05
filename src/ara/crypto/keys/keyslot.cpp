#include "ara/crypto/keys/Inher_key_slote.hpp"

#include <iostream>
namespace ara
{ 
    namespace crypto
    {
        namespace keys
        {
           
            ara::core::Result<KeySlotPrototypeProps> InhKeySlot :: GetPrototypedProps ()const noexcept
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
               ara::core::Result<KeySlotContentProps> InhKeySlot :: GetContentProps () const noexcept
                 {
                   //Return the key slot content properties 
                     return KSCP;
                  }
    
                ara::core::Result<cryp::CryptoProvider::Uptr> InhKeySlot ::MyProvider ()const noexcept
                  {
                  // return a pointer to the related CryptoProvider.
                 return Myprov;
                   }
    
                 ara::core::Result<void> InhKeySlot :: Clear () noexcept
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
