#include "ara/crypto/cryp/cryobj/sec_seed.hpp"
#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {

                SecSeed::SecSeed(AllowedUsageFlags allowedVal,bool sessionVar,bool exportableVar)
                {
                    allowed=allowedVal;
                    session=sessionVar;
                    exportable=exportableVar;

                } 
                
                SecretSeed::Uptr SecSeed::Clone (ReadOnlyMemRegion xorDelta=ReadOnlyMemRegion()) const
                {
                    cryptoobj cobj ;
                    //cobj.CO_ID.mCOType = this->kObjectType;
                    SecSeed::Uptr op=std::make_unique<SecSeed>(allowed,session,exportable);

                    if( sizeof(xorDelta) < sizeof(this->Seed_val))
                    {
                        for(int i = 0; i<sizeof(xorDelta);i++)
                         op->Seed_val[i] ^= xorDelta[i];
                    }
                    else
                    {
                        for(int i = 0; i<sizeof(this->Seed_val);i++)
                         op->Seed_val[i] ^= xorDelta[i];
                    }
                    
                    return op;

                }

                
                void SecSeed::JumpFrom (const SecSeed &from,std::int64_t steps)
                {
                    if(sizeof(from.Seed_val)>=sizeof(this->Seed_val))
                    {
                        if(steps != 0)
                        this->Seed =  from.Seed_val[from.Seed +steps] ;
                        else
                        this->Seed_val = from.Seed_val ;
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
                    ConcreteCryptoProvider *CCP;
                    SecSeed ::Uptrc upt= CCP->GenerateSeed(algId,allowed,session,exportable);
                    this->Seed_val = upt->Seed_val;
                    return *this;
                }

                
                SecretSeed& SecSeed::operator^= (const SecSeed &source)
                {
                    if(this != &source)
                    {
                        for(int i = 0; i<sizeof(source);i++)
                        this->Seed_val[i] ^= source.Seed_val[i];
                    }
                    return *this;
                }
                
                SecretSeed& SecSeed::operator^= (ReadOnlyMemRegion source)
                {
                    for(int i = 0; i<sizeof(source);i++)
                    this->Seed_val[i] ^= source[i];
                    return *this;
                }
        }
    }
}
