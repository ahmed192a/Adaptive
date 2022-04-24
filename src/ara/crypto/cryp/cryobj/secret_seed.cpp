#include "ara/crypto/cryp/cryobj/sec_seed.hpp"
#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
                ara::core::Result<SecretSeed::Uptr> SecSeed::Clone (ReadOnlyMemRegion xorDelta=ReadOnlyMemRegion()) const
                {
                    cryptoobj cobj ;
                    cobj.CO_ID.mCOType = this->kObjectType;
                    SecretSeed::Uptr Sc;
                    ara::core::Result<SecretSeed::Uptr> OP (Sc);
                    if( sizeof(xorDelta) < sizeof(this->seed_val))
                    {
                        //this->seed_val ^= xorDelta;
                    }
                    else
                    {
                        //this->seed_val ^= (xorDelta & (sizeof(this->seed_val) & 0xFFFF));

                    }
                    
                    return OP;

                }

                
                ara::core::Result<void> SecSeed::JumpFrom (const SecretSeed &from,std::int64_t steps)
                {
                    if(steps != 0)
                    this->seed_val = from.seed_val + steps ;
                    else
                    this->seed_val = from.seed_val ;
                   
                }

                SecretSeed& SecSeed::Jump (std::int64_t steps)
                {
                    this->seed_val = this->seed_val + steps ;
                    return *this ;
                }


                SecretSeed& SecSeed::Next ()
                {
                    this->seed_val = this->seed_val + 8;
                    return *this;
                }

                
                SecretSeed& SecSeed::operator^= (const SecretSeed &source)
                {
                    if(this != &source)
                    {
                        this->seed_val ^= source.seed_val;
                    }
                    return *this;
                }
                
                SecretSeed& SecSeed::operator^= (ReadOnlyMemRegion source)
                {
                    //this->seed_val ^= source;
                    return *this;
                }
        }
    }
}
