#include "ara/crypto/cryp/cryobj/symmetric_key.hpp"
#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            SymmetricKey:: SymmetricKey(AllowedUsageFlags allowedVal,bool sessionVar,bool exportableVar)
            {
                allowed=allowedVal;
                session=sessionVar;
                exportable=exportableVar;

            } 
        }
    }
}
