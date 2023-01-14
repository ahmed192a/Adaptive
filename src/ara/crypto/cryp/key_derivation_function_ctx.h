#ifndef ARA_CRYPTO_KDF_H
#define ARA_CRYPTO_KDF_H


#include "../common/mem_region.h"
#include "../common/base_id_types.h"
//#include "message_authn_code_ctx.h"
//#include "cryobj/restricted_use_object.h"
//#include "cryobj/secret_seed.h"
#include "crypto_context.h"



namespace ara {
    namespace crypto {
        namespace cryp {

            class KeyDerivationFunctionCtx : public CryptoContext{


             

                public:
                //KeyDerivationFunctionCtx()=default;
                using Uptr = std::unique_ptr<KeyDerivationFunctionCtx>; 


               /*1
               -Add Public Salt
               -The FC Crypto shall support salting to improve the secrecy of the derived key.
               -Add an application filler value stored in a (non-secret) ReadOnlyMemRegion. If (GetFillerSize()
                == 0), then this method call will be ignored.
               --shall add a salt value stored in the provided
                non-secret ReadOnlyMemRegion for subsequent key derivation
               --shall return a kInvalidInputSize error, if the size of the provided salt is not supported
                by the ara::crypto::CryptoAlgId used to instantiate this context.
               */
                            /**
               *  @brief Add Public Salt
               *
               *  @details
               *   The FC Crypto shall support salting to improve the secrecy of the derived key.
               *
               *  @param public_salt  Provided Salt Value.
               * 
               *  @return
               */
                virtual void AddSalt (SymmetricKey public_salt) noexcept=0;

                /*2
               -Add Private Salt
               -The FC Crypto shall support salting to improve the secrecy of the derived key.
               --shall add a secret salt value stored in the provided SecretSeed for subsequent key
                derivation.
               --shall return a kInvalidInputSize error, if the size of the provided secret salt
                 is not supported by the ara::crypto::CryptoAlgId used to instantiate this
                 context.

               */
                           /**
               *  @brief Add Private Salt
               *
               *  @details
               *   The FC Crypto shall support salting to improve the secrecy of the derived key.
               *
               *  @param private_salt  Provided Secret Salt Value.
               * 
               *  @return
               */
                virtual void AddSecretSalt ( SymmetricKey secret_salt) noexcept=0;
               

               /*3
               -Configure the number of iterations that will be applied by default. Implementation can restrict
               minimal and/or maximal value of the iterations number.
               -The FC Crypto shall allow to specify the number of iterations for generating keys. When no number or zero is given, the default number
               of iterations is used. Otherwise, the provided iterations is used. However, the implenmentation can restrict
                minimal and / or maximal value of the iterations number.
               --shall configure the number of
                iterations for subsequent key derivation. If the provided number of iterations is smaller
                or larger than the implementation of this interface supports, the interface shall return
                the actual number of iterations applied otherwise the interface shall return the provided
                number of iterations.
               --The stack vendor may restrict the maximum number of iterations to avoid overloading
                the system. The stack vendor may enforce a minimum number of itertions needed to
                derive a secure key
               */
              /**
               *  @brief Configure the number of iterations that will be applied by default
               *
               *  @details
               *   The FC Crypto shall allow to specify the number of iterations for generating keys. When no number or zero is given, the default number
               *   of iterations is used. Otherwise, the provided iterations is used
               *
               *  @param iterations  Provided number of iterations.
               * 
               *  @return
               */
                virtual std::uint32_t ConfigIterations (std::uint32_t iterations=0) noexcept=0;


            
               /*4
               -Derive a symmetric key from the provided key material and provided context configuration.
               --The interfaces ara::crypto::cryp::KeyDerivationFunctionCtx::DeriveKey and ara::crypto::cryp::KeyDerivationFunctionCtx::DeriveSeed shall 
                apply the configured key derivation algorithm for the provided context configuration. The interface shall return
                the derived key material as a SymetricKey or SecretSeed respectively. The returned objects
                shall be configured according to the provided flags isSession and isExportable.
                If the flags are not provided the object instance shall be session and not exportable.
                The interface shall return kUninitializedContext, if the configured key derivation
                algorithm requires more context configuration than provided.
               */

                 /**
               *  @brief Derive a symmetric key from the provided key material and provided context configuration using public salt.
               *
               *  @details
               *   Apply the configured key derivation algorithm for the provided context configuration.
               *
               *  @param isSession  defines the lifetime for the derived key.
               *  @param isExportable  defines if a derived key can be stored outside the system
               *  @return vector of bytes for the derived key
               */
               virtual std::vector<ara::crypto::byte> DeriveKey (bool isSession=true, bool isExportable=false)  noexcept=0;


                /*5
                -The FC Crypto shall allow to derive slave key material (secret seed) from provided master
                key material with optional public or secret salt. To use secret salt, an application or
                functional cluster uses the AddSecretSalt to provide a secret salt value to the context. The CryptoAPI 
                also supports adding a public salt by AddSalt. Deriving a slave
                key is done by the given target symmetric algorithm identifier, which also defines the
                target seed-length.
                -The FC Crypto shall allow to set the properties of the derived key as follow:
                • ”session” (or ”temporary”) attribute defines the lifetime for the derived key.
                • ”exportable” defines if a derived key can be stored outside the system
                --The interfaces ara::crypto::cryp::KeyDerivationFunctionCtx::DeriveKey and ara::crypto::cryp::KeyDerivationFunctionCtx::DeriveSeed shall apply the configured key derivation
                algorithm for the provided context configuration. The interface shall return the derived
                key material as a SymetricKey or SecretSeed respectively. The returned objects
                shall be configured according to the provided flags isSession and isExportable.
                If the flags are not provided the object instance shall be session and not exportable.
                The interface shall return kUninitializedContext, if the configured key derivation
                algorithm requires more context configuration than provided.
                */
               /**
               *  @brief Derive a symmetric key from the provided key material and provided context configuration using secret salt.
               *
               *  @details
               *   Apply the configured key derivation algorithm for the provided context configuration.
               *
               *  @param isSession  defines the lifetime for the derived key.
               *  @param isExportable  defines if a derived key can be stored outside the system
               *  @return vector of bytes for the derived key
               */
               virtual std::vector<ara::crypto::byte> DeriveSeed (bool isSession=true, bool isExportable=false)  noexcept=0;
                /*6
                -Clear the Crypto Context
                */
                /**
               *  @brief Clear the Crypto Context
               *
               *  @details
               *   Clear the Crypto Context
               * 
               *  @return 
               */
               
               virtual void Reset () noexcept=0;
                
               

                /*8
                -Get the size of the salt
                -Get the fixed size of an application specific "filler" required by this context instance. If this
                instance of the key derivation context does not support filler values, 0 shall be returned.
                Get the fixed size of the target key ID required by diversification algorithm. Returned value is
                constant for each instance of the interface, i.e. independent from configuration by
                */
               /**
               *  @brief Get the size of the salt
               *
               *  @details
               *   Get the fixed size of an application specific "filler" required by this context instance. If this
               *   instance of the key derivation context does not support filler values, 0 shall be returned.
               * 
               *  @return std::size_t size of the salt
               */
               virtual std::size_t GetKeyIdSize () const noexcept=0;

               /*9
               Get the symmetric algorithm ID of target (slave) key. If the context was not configured yet by a
               call of the Init() method then kAlgIdUndefined should be.
                */
               /**
               *  @brief Get the symmetric algorithm ID of target (slave) key
               *
               *  @details
               *   Get the symmetric algorithm ID of target (slave) key. If the context was not configured yet by a
               *     call of the Init() method then kAlgIdUndefined should be.
               * 
               *  @return CryptoAlgId
               */
               virtual CryptoAlgId GetTargetAlgId () const noexcept=0;



                /*10
                Get allowed key usage of target (slave) key. The returned value depends on the source
                key-material allowed usage flags and the argument allowedUsage of last call of the Init()
                method. If the context has not yet been configured by a call of the Init() method, the allowed
                usage flags of the source key-material shall be returned. If the context has not yet been
                configured by a call of the Init() method and no source key-material has been set either, kAllow
                KdfMaterialAnyUsage shall be returned.

                --shall return the allowed usage flags of the derived key.
                --If the context has not yet been configured by a call to ara::crypto::cryp:-:KeyDerivationFunctionCtx::Init and
                  a ara::crypto::cryp::RestrictedUseObject has been provided as source key material, the allowed
                  usage flags of the source key-material shall be returned.
                  • If the context has not yet been configured by a call to ara::crypto::cryp:-
                  :KeyDerivationFunctionCtx::Init and no ara::crypto::cryp::RestrictedUseObject has been provided as source key material, kAllowKdfMaterialAnyUsage shall be returned.
                  • If the context has been configured by a call to ara::crypto::cryp::KeyDerivationFunctionCtx::Init, the provided ara::crypto::AllowedUsageFlags shall be returned or kAllowKdfMaterialAnyUsage in case
                  ara::crypto::AllowedUsageFlags have not been provided.
                  
                */
               /**
               *  @brief Get allowed key usage of target (slave) key.
               *
               *  @details
               *   Get allowed key usage of target (slave) key. The returned value depends on the source
               * key-material allowed usage flags and the argument allowedUsage of last call of the Init()
               * method. If the context has not yet been configured by a call of the Init() method, the allowed
               * usage flags of the source key-material shall be returned. If the context has not yet been
               / configured by a call of the Init() method and no source key-material has been set either, kAllow
               * KdfMaterialAnyUsage shall be returned.
               *
               * 
               *  @return AllowedUsageFlags
               */
                //virtual AllowedUsageFlags GetTargetAllowedUsage () const noexcept=0;

                /*11
                Get the bit-length of target (diversified) keys. Returned value is configured by the context
                factory method, i.e. independent from configuration by.
                */
               /**
               *  @brief Get the bit-length of target (diversified) keys
               *
               *  @details
               *  Get the bit-length of target (diversified) keys. Returned value is configured by the context
               *  factory method, i.e. independent from configuration by.
               *
               * 
               *  @return size of the derived key.
               * */
                virtual std::size_t GetTargetKeyBitLength () const noexcept=0;

                /*12
                -During the initialization phase of
                the context, FC Crypto shall allow to parametrize a hash function as the used key
                derivation function. This is done by the algorithm identifier
                -Beside the usage of hashes, the FC Crypto shall allow to parametrize symmetric encryption algorithms
                 as the used key derivation function. This is done by the algorithm identifier as well.
                -Deriving the key is done by the given target symmetric algorithm identifier, which also defines a length
                of derived key
                --shall configure the key derivation by setting the
                provided targetKeyId, the optionally provided ara::crypto::CryptoAlgId,
                usage flags and context label of the derived key. The interface shall return:
                • kUsageViolation error, if a ara::crypto::cryp::RestrictedUseObject has been provided as source key material and its allowed usage flags are
                more restrictive than the allowed usage flags provided by this interface.
                • kIncompatibleArguments error, if the provided targetAlgId is incompatible with the size of the key material derived by the configured key derivation
                algorithm.
                */
                /**
               *  @brief Initialize the context.
               *
               *  @details
               *  Shall configure the key derivation by setting the
               *  provided targetKeyId, the optionally provided ara::crypto::CryptoAlgId,
               *  usage flags and context label of the derived key. 
               * 
               * @param  targetKeyId 
               * @param ctxLabel
               * @param AllowedUsageFlags
               * @param CryptoAlgId  
               *  @return 
               */
                virtual void Init (ReadOnlyMemRegion targetKeyId, ReadOnlyMemRegion ctxLabel,
                AllowedUsageFlags allowedUsage=kAllowKdfMaterialAnyUsage,
                CryptoAlgId targetAlgId=kAlgIdDefault)
                noexcept=0;
               
                /*13
                Set (deploy) key-material to the key derivation algorithm context.
                --shall deploy the provided data (ara::crypto::cryp::RestrictedUseObject or ReadOnlyMemRegion) as source input for key derivation. The interface shall return
                • kUsageViolation error, if the allowed usage flagkAllowKdfMaterial of the
                provided ara::crypto::cryp::RestrictedUseObject is not set.
                • kIncompatibleObject error, if the provided ara::crypto::cryp::RestrictedUseObject belongs to a different ara::crypto::cryp::CryptoProvider instance.
                • kBruteForceRisk error, if the provided source material is below a implementation defined size
                */
                /**
               *  @brief Set (deploy) key-material to the key derivation algorithm context.
               *
               *  @details
               *  Shall deploy the provided data as source input for key derivation.
               * 
               * @param sourceKM
               *  @return 
               */
                virtual void SetSourceKeyMaterial (const std::uint8_t sourceKM) noexcept=0;






            };

        



        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_KDF_H
