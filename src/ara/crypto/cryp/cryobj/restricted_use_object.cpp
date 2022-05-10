#include "ara/crypto/cryp/cryobj/rest_use_obj.hpp"

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
