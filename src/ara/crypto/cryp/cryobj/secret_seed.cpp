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
                    if( sizeof(xorDelta) < sizeof(this->Seed_val))
                    {
                        //this->seed_val ^= xorDelta;
                    }
                    else
                    {
                        //this->seed_val ^= (xorDelta & (sizeof(this->seed_val) & 0xFFFF));

                    }
                    
                    return OP;

                }

                
                ara::core::Result<void> SecSeed::JumpFrom (const SecSeed &from,std::int64_t steps)
                {
                    if(sizeof(from.Seed_val)>=sizeof(this->Seed_val))
                    {
                        if(steps != 0)
                        this->Seed =  from.Seed_val[from.Seed +steps] ;
                        else
                        this->Seed = from.Seed ;
                    }
                    else
                    {
                        //do nothing
                    }
                   
                }

                SecretSeed& SecSeed::Jump (std::int64_t steps)
                {
                    if(steps != 0)
                     this->Seed =  this->Seed_val[this->Seed +steps] ;
                    else
                     this->Seed = this->Seed ;
                    return *this ;
                }


                SecretSeed& SecSeed::Next ()
                {
                    this->Seed = this->Seed_val[this->Seed + 1];
                    return *this;
                }

                
                SecretSeed& SecSeed::operator^= (const SecSeed &source)
                {
                    if(this != &source)
                    {
                        this->Seed ^= source.Seed_val[this->Seed];
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
