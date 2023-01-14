#include "ara/crypto/cryp/cryobj/rest_use_obj.h"

#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            
            RestrictedUseObject::Usage RestUseObj::GetAllowedUsage () const noexcept 
            {
                return this->Allow_U;
            }
        }
    }
}
