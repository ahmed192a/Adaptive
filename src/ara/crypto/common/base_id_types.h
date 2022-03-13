#ifndef ARA_CRYPTO_BASE_ID_TYPES_H
#define ARA_CRYPTO_BASE_ID_TYPES_H

namespace ara
{
  namespace crypto
  {
  
    
    namespace cryp
    {
     //SWS_CRYPT_10016
     /**
      * defines all types of crypto objects (types of content that can be stored to a key slot)
      */
      enum class CryptoObjectType : std::uint32_t 
      {
         kUndefined=0,
         kSymmetricKey=1,
         kPrivateKey=2,
         kPublicKey=3,
         kSignature=4,
         kSecretSeed=5
      };
    }
      
      //SWS_CRYPT_10018
      /**
      *  defines key-slot types; currently only machine and applicaiton key-slots are defined
      */
      enum class KetSlotType : std::uint32_t
      {
        kMachine= 1, 
        kApplication= 2
      };
    
      //SWS_CRYPT_10019
      /**
      * defines cryptographic transformations 
      */
      enum class CryptoTransform : std::uint32_t 
      {
       kEncrypt= 1,
       kDecrypt= 2,
       kMacVerify= 3,
       kMacGenerate= 4,
       kWrap= 5,
       kUnwrap= 6,
       kSigVerify= 7,
       kSigGenerate= 8
      };
