#include "ara/crypto/cryp/HKDF.hpp"
#include "ara/crypto/cryp/concrete_crypto_provider.hpp"


using namespace ara::crypto;
using namespace ara::crypto::cryp;



            HKDF::HKDF(CryptoProvider * provider) {
                this->myProvider = provider;
            }


            /** Inherited from CryptoContext class**/
            bool HKDF::IsInitialized() const noexcept{
                if(status == 0)
                    return false;
                else
                    return true;
            }


            CryptoProvider& HKDF::MyProvider() const noexcept {
                return (*myProvider) ;
            }

            // CryptoPrimitiveId::Uptr HMAC::GetCryptoPrimitiveId() const noexcept {
            //     return (this->myProvider->ConvertToAlgId("test"));

            // }

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
                /*virtual */void HKDF::AddSalt (SymmetricKey public_salt) /*noexcept=0*/{
                    this->public_salt=public_salt;
                    saltAdded=0;
                    
                }

                /*2
               -Add Private Salt
               -The FC Crypto shall support salting to improve the secrecy of the derived key.
               --shall add a secret salt value stored in the provided SecretSeed for subsequent key
                derivation.
               --shall return a kInvalidInputSize error, if the size of the provided secret salt
                 is not supported by the ara::crypto::CryptoAlgId used to instantiate this
                 context.
               */
                /*virtual */void HKDF::AddSecretSalt (SymmetricKey secret_salt) /*noexcept=0*/{
                    this->secret_salt=secret_salt; 
                    saltAdded=1;
                }
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
                std::uint32_t HKDF::ConfigIterations (std::uint32_t iterations=0) /*noexcept=0*/{
                    this->iterations=iterations;
                    return this->iterations;
                }
                /*4
               -Derive a symmetric key from the provided key material and provided context configuration.
               --The interfaces ara::crypto::cryp::HKDF::DeriveKey and ara::crypto::cryp::HKDF::DeriveSeed shall 
                apply the configured key derivation algorithm for the provided context configuration. The interface shall return
                the derived key material as a SymetricKey or SecretSeed respectively. The returned objects
                shall be configured according to the provided flags isSession and isExportable.
                If the flags are not provided the object instance shall be session and not exportable.
                The interface shall return kUninitializedContext, if the configured key derivation
                algorithm requires more context configuration than provided.
               */
                         

               /*virtual */std::vector<ara::crypto::byte> HKDF::DeriveKey (bool isSession=true, bool isExportable=false)  /*noexcept=0*/{
                    ConcreteCryptoProvider * c;
                    HMAC hmac(c);
                    hmac.Start();
                    //conversion
                    hmac.SetKey((this->public_salt)); //ReadOnlyMemRegion *
                    
                    //conversion
                    hmac.Update(this->sourceKM); //RestrictedUseObject * 
                    hmac.Finish();

                    return hmac.GetDigest();


                //void Reset() noexcept;
                //void SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) noexcept;

                //void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept;
                //// void Start(const SecretSeed &iv) noexcept;

                //// bool Check(const Signature &expected) const noexcept;

                //// void Update(const RestrictedUseObject &in) noexcept;
                //// void Update(ReadOnlyMemRegion in) noexcept;
                //void Update(std::uint8_t in) noexcept;

                //DigestService::Uptr GetDigestService() const noexcept;
                //std::vector<ara::crypto::byte> GetDigest(std::size_t offset = 0) const noexcept;
    
                //Signature::Uptrc Finish(bool makeSignatureObject = false) noexcept;

                
               }

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
                --The interfaces ara::crypto::cryp::HKDF::DeriveKey and ara::crypto::cryp::HKDF::DeriveSeed shall apply the configured key derivation
                algorithm for the provided context configuration. The interface shall return the derived
                key material as a SymetricKey or SecretSeed respectively. The returned objects
                shall be configured according to the provided flags isSession and isExportable.
                If the flags are not provided the object instance shall be session and not exportable.
                The interface shall return kUninitializedContext, if the configured key derivation
                algorithm requires more context configuration than provided.
                */
               /*virtual */std::vector<ara::crypto::byte> HKDF::DeriveSeed (bool isSession=true, bool isExportable=false)  /*noexcept=0*/{
                    
                    ConcreteCryptoProvider * c;
                    HMAC hmac(c);
                    hmac.Start();
                    
                    //conversion
                    hmac.SetKey((this->secret_salt)); //ReadOnlyMemRegion *
                    
                    //conversion
                    hmac.Update(this->sourceKM); //RestrictedUseObject * 
                    hmac.Finish();

                    return hmac.GetDigest();
               }

                  /*6
                -Clear the Crypto Context
                */
               /*virtual */void HKDF::Reset () /*noexcept=0*/{
                this->targetKeyId=nullptr;//12
                CryptoAlgId targetAlgIdTemp;//12
                this->targetAlgId=targetAlgIdTemp;
                AllowedUsageFlags allowedUsageTemp;//12
                allowedUsage=allowedUsageTemp;
                this->ctxLabel=nullptr;//12

                std::uint8_t sourceKMTemp;
                this->sourceKM=sourceKMTemp; //13
                
                SymmetricKey  public_saltTemp; //1
                this->public_salt=public_saltTemp; //1

                SymmetricKey  secret_saltTemp; //1
                this->secret_salt=secret_saltTemp; //2
                iterations=0;//3
               } 
               /*8
                -Get the size of the salt
                -Get the fixed size of an application specific "filler" required by this context instance. If this
                instance of the key derivation context does not support filler values, 0 shall be returned.
                Get the fixed size of the target key ID required by diversification algorithm. Returned value is
                constant for each instance of the interface, i.e. independent from configuration by
                */
               /*virtual */std::size_t HKDF::GetKeyIdSize () const /*noexcept=0*/{
                   if(saltAdded==0){
                    return 0;
                    
                   }
                   else{
                    return this->HKDF_input_key_len;
                   }
               }
               

                /*9
               Get the symmetric algorithm ID of target (slave) key. If the context was not configured yet by a
               call of the Init() method then kAlgIdUndefined should be.
                */
                 using CryptoAlgId = std::uint64_t;
                CryptoAlgId HKDF::GetTargetAlgId () const /*noexcept=0*/{
                    if(isContextConfigured==0){
                        return kAlgIdUndefined;
                    }
                    else{
                         return this->targetAlgId;
                    }
                }
                /*10
                Get allowed key usage of target (slave) key. The returned value depends on the source
                key-material allowed usage flags and the argument allowedUsage of last call of the Init()
                method. If the context has not yet been configured by a call of the Init() method, the allowed
                usage flags of the source key-material shall be returned. If the context has not yet been
                configured by a call of the Init() method and no source key-material has been set either, kAllow
                KdfMaterialAnyUsage shall be returned.
                */
               // using AllowedUsageFlags = std::uint32_t;
               // AllowedUsageFlags HKDF::GetTargetAllowedUsage () const  /*noexcept=0*/{
               //     if( (this->isContextConfigured==0)&&(this->sourceKM==nullptr) ){
               //         return kAllowKdfMaterialAnyUsage;
               //     }
               //     else if(this->isContextConfigured==0){
               //          return this->sourceKM->GetAllowedUsage();
               //     }
               // }
                
                /*11
                Get the bit-length of target (diversified) keys. Returned value is configured by the context
                factory method, i.e. independent from configuration by.
                */
                /*virtual*/ std::size_t HKDF::GetTargetKeyBitLength () const /*noexcept=0*/{
                    return HKDF_output_len;
                }
                

                /*12
                -During the initialization phase of
                the context, FC Crypto shall allow to parametrize a hash function as the used key
                derivation function. This is done by the algorithm identifier
                -Beside the usage of hashes, the FC Crypto shall allow to parametrize symmetric encryption algorithms
                 as the used key derivation function. This is done by the algorithm identifier as well.
                -Deriving the key is done by the given target symmetric algorithm identifier, which also defines a length
                of derived key
                ---ctxLabel->Even if two apps have the same SK, they get independent keys
                */
                /*virtual */void HKDF::Init (ReadOnlyMemRegion targetKeyId, ReadOnlyMemRegion ctxLabel,
                AllowedUsageFlags allowedUsage=kAllowKdfMaterialAnyUsage,
                CryptoAlgId targetAlgId=kAlgIdDefault)
                /*noexcept*/{
                    this->targetKeyId=&targetKeyId;
                    this->targetAlgId=targetAlgId;
                    this->allowedUsage=allowedUsage;
                    this->ctxLabel=&ctxLabel;

                    status=1;
                    
                }

                /*13
                Set (deploy) key-material to the key derivation algorithm context.
                */
                /*virtual */void HKDF::SetSourceKeyMaterial (const std::uint8_t sourceKM) /*noexcept=0*/{
                    this->sourceKM=sourceKM;
                }


               










