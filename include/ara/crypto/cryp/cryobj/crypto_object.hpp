#pragma once
//#include <memory>
#include <iostream>
#include "../../../core/result.hpp"
#include "crypto_pr_id.hpp"
#include "../../common/crypto_object_uid.hpp"

namespace ara
{
    namespace crypto
    {
        class ConcreteIOInterface;
        namespace cryp
        {
            /**
             * SWS_CRYPT_20500
            * @file crypto_object.hpp
            * @brief A common interface for all cryptograhic objects recognizable by the Crypto Provider.
            **/
            class CryptoObject 
            {
                public:
              
                struct COIdentifier
                {
                    CryptoObjectType mCOType;
                    CryptoObjectUid mCouid;
                };
                 
                
                // COIdentifier CO_ID;
                 /*
                * SWS_CRYPT_20502
                * Unique smart pointer of the constant interface.
                */
                using Uptrc = std::unique_ptr<const CryptoObject>;
                /*
                * SWS_CRYPT_20501
                * Unique smart pointer of the interface.
                * smart pointer to allocate and free in memory automatically 
                * and cant make a copy from it
                */
                using Uptr = std::unique_ptr<CryptoObject>;
                
                /**
                * SWS_CRYPT_20503
                * @file crypto_object.hpp
                * @brief Destructor
                * 
                */
            virtual ~CryptoObject () noexcept=default;
                
            /**
             * SWS_CRYPT_20518
             * @file crypto_object.hpp
             * @brief  Downcast and move unique smart pointer from the generic CryptoObject interface to concrete derived object. 
             * Return value: ara::core::Result< typename Concrete Object::Uptrc >
             unique smart pointer to downcasted constant interface of specified derived type
            *  
            **/ 
              
            
            
            // template <class ConcreteObject> static typename ConcreteObject::Uptrc Downcast(CryptoObject::Uptrc &&object) noexcept;                
            /**
             * SWS_CRYPT_20505
             * @file crypto_object.hpp
             * @brief Return the CryptoPrimitivId of this CryptoObject. 
            **/
            virtual CryptoPrId::Uptr GetCryptoPrimitiveId () const noexcept=0;
            
            /**
             * SWS_CRYPT_20514
             * @file crypto_object.hpp
             * @brief Return the object’s COIdentifier, which includes the object’s type and UID. An object that has no
               assigned COUID cannot be (securely) serialized / exported or saved to a non-volatile storage.
             *
             * 
            **/
            virtual COIdentifier GetObjectId () const noexcept=0;
             
             
            /**   
             * SWS_CRYPT_20516
             * @file crypto_object.hpp
             * @brief Return actual size of the object’s payload. Returned value always must be less than or equal to the maximum payload size expected for this primitive and object type
             * 
            **/
            
            virtual std::size_t GetPayloadSize () const noexcept=0;
            
            /**
             * SWS_CRYPT_20513
             * @file crypto_object.hpp
             * @brief Return value: bool -> true if the object is exportable (i.e. if it can be exported outside the trusted environment of the Crypto Provider)
             * 
            **/
            
            virtual bool IsExportable () const noexcept=0;
            
            
            /**
             * SWS_CRYPT_20512
             * @file crypto_object.hpp
             * @brief Return value: bool true if the object is temporay (i.e. its life time is limited by the current session only)
             * 
            **/
            virtual bool IsSession () const noexcept=0;
            
            /**
             * SWS_CRYPT_20517
             * @file crypto_object.hpp
             * @brief Save itself to provided IOInterface A CryptoObject with property "session" cannot be saved in a KeySlot.
            **/
            
            virtual void Save (ara::crypto::ConcreteIOInterface& container) const noexcept=0;
            
            /**
             * SWS_CRYPT_30208
             * @file crypto_object.hpp
             * @brief Copy-assign another CryptoObject to this instance.
             * 
            **/
            CryptoObject& operator= (const CryptoObject &other)=default;
            
            /**
             * SWS_CRYPT_30209
             * @file crypto_object.hpp
             * @brief Move-assign another CryptoObject to this instance.
             * 
            **/
            CryptoObject& operator= (CryptoObject &&other)=default;
            
            
            };
        }
    }
}
