#ifndef ARA_CRYPTO_BASE_ID_TYPES_H
#define ARA_CRYPTO_BASE_ID_TYPES_H
#include <string>
namespace ara
{
  namespace crypto
  {
    // not in the Crypto documentation but we need it in all classes
    using byte = uint8_t;

    //SWS_CRYPT_10014
    /**
     * @brief Container type of the Crypto Algorithm Identifier.
     * @file base_id_types.hpp
     */
    using CryptoAlgId = std::uint64_t;
    
    const CryptoAlgId kAlgIdUndefined = 0u;

    const CryptoAlgId kAlgIdDefault = kAlgIdUndefined;

    const CryptoAlgId kAlgIdNone = kAlgIdUndefined;
    //SWS_CRYPT_10015
    /**
     * @brief A container type and constant bit-flags of allowed usages of a key or a secret seed object. 
     * Only directly specified usages of a key are allowed,
     * all other are prohibited! Similar set of flags are defined for the usage restrictions of original key/seed and for 
     * a symmetric key or seed that potentially can be derived from the original one.
     */
    using AllowedUsageFlags = std::uint32_t;
    
    const AllowedUsageFlags kAllowDataEncryption = 0x0001;
    const AllowedUsageFlags kAllowDataDecryption = 0x0002;
    const AllowedUsageFlags kAllowDerivedDataDecryption = kAllowDataDecryption << 16;
    const AllowedUsageFlags kAllowDerivedDataEncryption = kAllowDataEncryption << 16;
    const AllowedUsageFlags kAllowExactModeOnly = 0x8000;
    const AllowedUsageFlags kAllowKdfMaterial = 0x0080;
    const AllowedUsageFlags kAllowKeyAgreement = 0x0010;
    const AllowedUsageFlags kAllowKeyDiversify = 0x0020;
    const AllowedUsageFlags kAllowKeyExporting = 0x0100;
    const AllowedUsageFlags kAllowKeyImporting = 0x0200;
    const AllowedUsageFlags kAllowPrototypedOnly = 0;
    const AllowedUsageFlags kAllowRngInit = 0x0040;
    const AllowedUsageFlags kAllowSignature = 0x0004;
    const AllowedUsageFlags kAllowVerification = 0x0008;
    const AllowedUsageFlags kAllowDerivedRngInit = kAllowRngInit << 16;
    const AllowedUsageFlags kAllowDerivedExactModeOnly = kAllowExactModeOnly << 16;
    const AllowedUsageFlags kAllowDerivedKdfMaterial = kAllowKdfMaterial<< 16;
    const AllowedUsageFlags kAllowDerivedKeyDiversify = kAllowKeyDiversify<< 16;
    const AllowedUsageFlags kAllowDerivedKeyExporting = kAllowKeyExporting<< 16;
    const AllowedUsageFlags kAllowDerivedKeyImporting = kAllowKeyImporting<< 16;
    const AllowedUsageFlags kAllowDerivedSignature = kAllowSignature <<16;
    const AllowedUsageFlags kAllowDerivedVerification = kAllowVerification<< 16;
    
    const AllowedUsageFlags kAllowKdfMaterialAnyUsage = kAllowKdfMaterial |
    kAllowDerivedDataEncryption | kAllowDerivedDataDecryption | kAllowDerivedSignature | kAllowDerivedVerification | 
    kAllowDerivedKeyDiversify | kAllowDerivedRngInit | kAllowDerivedKdfMaterial | 
    kAllowDerivedKeyExporting | kAllowDerivedKeyImporting;
    
    
     //SWS_CRYPT_10016
     /**
      * defines all types of crypto objects (types of content that can be stored to a key slot)
      */
    //The key/seed can be used for data encryption initialization (applicable to symmetric and asymmetric algorithms).//
     //const AllowedUsageFlags kAllowDataEncryption = 0x0001;
     //The key/seed can be used for data decryption initialization (applicable to symmetric and asymmetric algorithms).//s
     //const AllowedUsageFlags kAllowDataDecryption = 0x0002;
      enum class CryptoObjectType : std::uint32_t 
      {
         kUndefined=0,
         kSymmetricKey=1,
         kPrivateKey=2,
         kPublicKey=3,
         kSignature=4,
         kSecretSeed=5
      };
      
      //SWS_CRYPT_10018
      /**
      *  defines key-slot types; currently only machine and applicaiton key-slots are defined
      */
      enum class KeySlotType : std::uint32_t
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
  } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_BASE_ID_TYPES_H
