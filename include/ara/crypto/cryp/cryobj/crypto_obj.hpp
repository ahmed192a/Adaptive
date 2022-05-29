#pragma once
//#include <memory>
#include <iostream>
#include "crypto_object.hpp"
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            
            /**
             * SWS_CRYPT_20500
            * @file crypto_obj.hpp
            * @brief A common interface for all cryptograhic objects recognizable by the Crypto Provider.
            **/
            class cryptoobj : CryptoObject 
            {
                public:
               /**
                 * @brief required attributes to signature class
                 * 
                 */
                std::size_t H_Req_Size ;
                CryptoPrId::AlgId H_SingID;
               
                /**
                 * @brief required attributes to restricted class
                 * 
                 */
                AllowedUsageFlags Allow_U;
                
                /**
                 * SWS_CRYPT_20504
                 * @file crypto_object.hpp
                 * @brief Unique identifier of this CryptoObject
                 * 
                 */
                 
                 COIdentifier CO_ID;

                 //size of the value of key/seed/signature in bytes
                std::size_t payloadSize;
                bool session;
                bool exportable;

                 cryptoobj()=default;
                 cryptoobj(std::size_t payloadSize , bool session,bool exportable);
                 /*
                * SWS_CRYPT_20502
                * Unique smart pointer of the constant interface.
                */
                using Uptrc = std::unique_ptr<const cryptoobj>;
                /*
                * SWS_CRYPT_20501
                * Unique smart pointer of the interface.
                * smart pointer to allocate and free in memory automatically 
                * and cant make a copy from it
                */
                using Uptr = std::unique_ptr<cryptoobj>;
                
                
            /**
             * SWS_CRYPT_20518
             * @file crypto_obj.hpp
             * @brief  Downcast and move unique smart pointer from the generic CryptoObject interface to concrete derived object. 
             * Return value: ara::core::Result< typename Concrete Object::Uptrc >
             unique smart pointer to downcasted constant interface of specified derived type
            *  
            **/ 
              
            
            template <class ConcreteObject> static typename ConcreteObject::Uptrc Downcast(CryptoObject::Uptrc &&object) noexcept;
                
            /**
             * SWS_CRYPT_20505
             * @file crypto_obj.hpp
             * @brief Return the CryptoPrimitivId of this CryptoObject. 
            **/
            
             CryptoPrId::Uptr GetCryptoPrimitiveId () const noexcept;

            
            /**
             * SWS_CRYPT_20514
             * @file crypto_obj.hpp
             * @brief Return the object’s COIdentifier, which includes the object’s type and UID. An object that has no
               assigned COUID cannot be (securely) serialized / exported or saved to a non-volatile storage.
             *
             * 
            **/
             CryptoObject::COIdentifier GetObjectId () const noexcept;
             
             
            /**   
             * SWS_CRYPT_20516
             * @file crypto_obj.hpp
             * @brief Return actual size of the object’s payload. Returned value always must be less than or equal to the maximum payload size expected for this primitive and object type
             * 
            **/
            
             std::size_t GetPayloadSize () const noexcept;
            
            /**
             * SWS_CRYPT_20513
             * @file crypto_obj.hpp
             * @brief Return value: bool -> true if the object is exportable (i.e. if it can be exported outside the trusted environment of the Crypto Provider)
             * 
            **/
            
             bool IsExportable () const noexcept;
            
            
            /**
             * SWS_CRYPT_20512
             * @file crypto_obj.hpp
             * @brief Return value: bool true if the object is temporay (i.e. its life time is limited by the current session only)
             * 
            **/
             bool IsSession () const noexcept;
            
            /**
             * SWS_CRYPT_20517
             * @file crypto_obj.hpp
             * @brief Save itself to provided IOInterface A CryptoObject with property "session" cannot be saved in a KeySlot.
            **/
            
            //void Save (ara::crypto::ConcreteIOInterface& container) const noexcept;
            
            /**
             * SWS_CRYPT_30208
             * @file crypto_obj.hpp
             * @brief Copy-assign another CryptoObject to this instance.
             * 
            **/
            cryptoobj& operator= (const cryptoobj &other);
            
            /**
             * SWS_CRYPT_30209
             * @file crypto_obj.hpp
             * @brief Move-assign another CryptoObject to this instance.
             * 
            **/
            cryptoobj& operator= (cryptoobj &&other);
            
            
            };
        }
    }
}
