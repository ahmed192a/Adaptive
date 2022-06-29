#include "ara/crypto/keys/Inher_key_slote.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
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
                file <<"KSCP.mAlgId=" << std::endl;
                file <<"KSCP.mObjectType="<<std::endl;
                file <<"KSCP.mObjectUid.mGeneratorUid.mQwordLs=" <<std::endl;
                file <<"KSCP.mObjectUid.mGeneratorUid.mQwordMs=" <<std::endl;
                file <<"KSCP.mObjectUid.mVersionStamp=" <<std::endl;
                file <<"KSCP.mContentAllowedUsage=" <<std::endl;
                file <<"KSCP.mObjectSize="<<std::endl;
                file <<"KSPP.mSlotCapacity="<<std::endl;
                file <<"KSPP.mSlotType=" <<std::endl;
                file <<"KSPP.mAlgId="<<std::endl;
                file <<"KSPP.mAllocateSpareSlot=" <<std::endl;
                file <<"KSPP.mAllowContentTypeChange=" <<std::endl;
                file <<"KSPP.mMaxUpdateAllowed=" <<std::endl;
                file <<"KSPP.mExportAllowed=" <<std::endl;
                file <<"KSPP.mContentAllowedUsage=" <<std::endl;
                file <<"KSPP.mObjectType=" <<std::endl;

            }


               /*
               Check the slot for emptiness
               */

            bool InhKeySlot::IsEmpty() noexcept 
            {
                if (Empty_State)
                {
                    return true;//true if the slot is empty or false otherwise//
                }
                else
                    return false;
            }
                
            /*
            **Save the content of a provided source IOInterface to this key - slot
            */
            
            void InhKeySlot::SaveCopy(const ConcreteIOInterface& container) noexcept
            { 

                if(!(container.IsIOInterface_State_Empty()))//if the source IOInterface isn't empty//
                {
                    std::ofstream my_file;
                    std::string File_Name = path;
                    my_file.open(File_Name,std::ofstream::out | std::ofstream::trunc);
                    my_file.open(File_Name,std::ios_base::app);
                    //Key Slot Content Properties Struct variables //
                    KSCP.mAlgId = container.GetPrimitiveId();
                    //write it in the file //
                    my_file <<"KSCP.mAlgId=" + std::to_string(container.GetPrimitiveId())<< std::endl;
                    //-----------------------------------------------//
                    KSCP.mObjectType = container.GetCryptoObjectType();
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mObjectType="+ CryptoObjectType_tostring[(uint32_t)container.GetCryptoObjectType()]<<std::endl;
                    //----------------------------------------------//
                    KSCP.mObjectUid = container.GetObjectId();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mObjectUid.mGeneratorUid.mQwordLs=" + std::to_string(container.GetObjectId().mGeneratorUid.mQwordLs)<<std::endl;
                    my_file <<"KSCP.mObjectUid.mGeneratorUid.mQwordMs=" + std::to_string(container.GetObjectId().mGeneratorUid.mQwordMs)<<std::endl;
                    my_file <<"KSCP.mObjectUid.mVersionStamp=" + std::to_string(container.GetObjectId().mVersionStamp)<<std::endl;
                    //----------------------------------------------//
                    KSCP.mContentAllowedUsage = container.GetAllowedUsage();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mContentAllowedUsage=" + std::to_string(container.GetAllowedUsage())<<std::endl;
                    //----------------------------------------------//
                    KSCP.mObjectSize = container.GetCapacity();//shall return capacity of the underlying resource in bytes//
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mObjectSize=" + std::to_string(container.GetCapacity())<<std::endl;
                    //----------------------------------------------//
                    //Key Slot Prototypes Struct variables//
                    KSPP.mSlotCapacity= container.GetCapacity();//shall return capacity of the underlying resource in bytes//
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mSlotCapacity=" + std::to_string(container.GetCapacity())<<std::endl;
                    //----------------------------------------------//
                    KSPP.mSlotType = container.GetSlotType();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mSlotType=" + KeySlotType_tostring[(uint32_t)container.GetSlotType()+1]<<std::endl;
                    //----------------------------------------------//
                    KSPP.mAlgId = container.GetPrimitiveId();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mAlgId=" + std::to_string(container.GetPrimitiveId())<<std::endl;
                    //----------------------------------------------//
                    //Elli etghyr//
                    KSPP.mAllocateSpareSlot = container.IsAllocateSpareSlot();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mAllocateSpareSlot=" + std::to_string(container.IsAllocateSpareSlot())<<std::endl;
                    //----------------------------------------------//
                    KSPP.mAllowContentTypeChange = container.IsAllowContentTypeChange();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mAllowContentTypeChange=" + std::to_string(container.IsAllowContentTypeChange())<<std::endl;
                    //----------------------------------------------//
                    KSPP.mMaxUpdateAllowed = container.GetMaxUpdateAllowed();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mMaxUpdateAllowed=" + std::to_string(container.GetMaxUpdateAllowed())<<std::endl;
                    //----------------------------------------------//
                    KSPP.mExportAllowed=container.IsExportAllowed();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mExportAllowed=" + std::to_string(container.IsExportAllowed())<<std::endl;
                    //----------------------------------------------//
                    KSPP.mContentAllowedUsage=container.GetAllowedUsage();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mContentAllowedUsage=" + std::to_string(container.GetAllowedUsage())<<std::endl;
                    //----------------------------------------------//
                    KSPP.mObjectType = container.GetTypeRestriction();
                      my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mObjectType=" + CryptoObjectType_tostring[(uint32_t)container.GetTypeRestriction()]<<std::endl;

                    //----------------------------------------------//
                    //change state of key slot to committed //
                    this->state = SlotState::commited;
                    Empty_State=false;
                
                }
            
            }


             /**
              * Open this key slot and return an IOInterface to its content
              **/
              
             ConcreteIOInterface::Uptr InhKeySlot::Open(bool subscribeForUpdates, bool writeable) noexcept
           {

             //instance of IOInterface//
                 ConcreteIOInterface::Uptr IOContent = std::make_unique<ConcreteIOInterface>();
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
               std::ofstream my_file;
                    std::string File_Name = path;
                    my_file.open(File_Name,std::ofstream::out | std::ofstream::trunc);
                    my_file.open(File_Name,std::ios_base::app);
                    //write it in the file //
                    my_file <<"KSCP.mAlgId=" + std::to_string(0)<< std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mObjectType="+ CryptoObjectType_tostring[0]<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mObjectUid.mGeneratorUid.mQwordLs=" + std::to_string(0)<<std::endl;
                    my_file <<"KSCP.mObjectUid.mGeneratorUid.mQwordMs=" + std::to_string(0)<<std::endl;
                    my_file <<"KSCP.mObjectUid.mVersionStamp=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mContentAllowedUsage=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSCP.mObjectSize=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mSlotCapacity=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mSlotType=" + KeySlotType_tostring[0]<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mAlgId=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mAllocateSpareSlot=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mAllowContentTypeChange=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mMaxUpdateAllowed=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mExportAllowed=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mContentAllowedUsage=" + std::to_string(0)<<std::endl;
                    my_file.open(File_Name,std::ios_base::app);
                    my_file <<"KSPP.mObjectType=" + CryptoObjectType_tostring[0]<<std::endl;


            }




            //KeySlot& InhKeySlot ::operator= (const KeySlot &other)
            //{
            //    if(this != &other)
            //    {
            //        this->KSCP.mAlgId = other.KSCP.mAlgId;
            //        this->KSCP.mContentAllowedUsage = other.KSCP.mContentAllowedUsage;
            //        this->KSCP.mObjectSize = other.KSCP.mObjectSize;
            //        this->KSCP.mObjectUid.mGeneratorUid.mQwordLs=other.KSCP.mObjectUid.mGeneratorUid.mQwordLs;
            //        this->KSCP.mObjectUid.mGeneratorUid.mQwordMs=other.KSCP.mObjectUid.mGeneratorUid.mQwordMs;
            //        this->KSCP.mObjectUid.mVersionStamp=other.KSCP.mObjectUid.mVersionStamp;
            //        this->KSCP.mObjectType =other.KSCP.mObjectType;
            //        this->Myprov ;

            //        this->KSPP.mAlgId = other.KSPP.mAlgId ;
            //        this->KSPP.mAllocateSpareSlot = other.KSPP.mAllocateSpareSlot ;
            //        this->KSPP.mAllowContentTypeChange = other.KSPP.mAllowContentTypeChange ;
            //        this->KSPP.mContentAllowedUsage = other.KSPP.mContentAllowedUsage ;
            //        this->KSPP.mExportAllowed = other.KSPP.mExportAllowed ;
            //        this->KSPP.mMaxUpdateAllowed = other.KSPP.mMaxUpdateAllowed ;
            //        this->KSPP.mObjectType = other.KSPP.mObjectType ;
            //        this->KSPP.mSlotCapacity = other.KSPP.mSlotCapacity ;
            //        this->KSPP.mSlotType = other.KSPP.mSlotType;
            //        
            //    }
            //    return *this;
            //}


            //KeySlot& InhKeySlot ::operator= (KeySlot &&other)
            //{
            //    if(this != &other)
            //    {
            //        this->KSCP.mAlgId = other.KSCP.mAlgId;
            //        this->KSCP.mContentAllowedUsage = other.KSCP.mContentAllowedUsage;
            //        this->KSCP.mObjectSize = other.KSCP.mObjectSize;
            //        this->KSCP.mObjectUid.mGeneratorUid.mQwordLs=other.KSCP.mObjectUid.mGeneratorUid.mQwordLs;
            //        this->KSCP.mObjectUid.mGeneratorUid.mQwordMs=other.KSCP.mObjectUid.mGeneratorUid.mQwordMs;
            //        this->KSCP.mObjectUid.mVersionStamp=other.KSCP.mObjectUid.mVersionStamp;
            //        this->KSCP.mObjectType =other.KSCP.mObjectType;
            //        this->Myprov ;

            //        this->KSPP.mAlgId = other.KSPP.mAlgId ;
            //        this->KSPP.mAllocateSpareSlot = other.KSPP.mAllocateSpareSlot ;
            //        this->KSPP.mAllowContentTypeChange = other.KSPP.mAllowContentTypeChange ;
            //        this->KSPP.mContentAllowedUsage = other.KSPP.mContentAllowedUsage ;
            //        this->KSPP.mExportAllowed = other.KSPP.mExportAllowed ;
            //        this->KSPP.mMaxUpdateAllowed = other.KSPP.mMaxUpdateAllowed ;
            //        this->KSPP.mObjectType = other.KSPP.mObjectType ;
            //        this->KSPP.mSlotCapacity = other.KSPP.mSlotCapacity ;
            //        this->KSPP.mSlotType = other.KSPP.mSlotType;
            //        
            //    }
            //    return *this;
            //}
           
         }
     }
 }
