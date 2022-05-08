#include "ara/crypto/cryp/cryobj/symmetric_key.hpp"
#include <iostream>
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief Defualt constructor
             * 
             * @return SymmetricKey 
             */
            SymmetricKey ::SymmetricKey(): allowed(0xffff),session(true),exportable(false) {}
            /**
             * @brief 
             * 
             * @param allowedVal 
             * @param sessionVar 
             * @param exportableVar 
             * @return SymmetricKey:: 
             */
            SymmetricKey:: SymmetricKey(AllowedUsageFlags allowedVal,bool sessionVar,bool exportableVar)
            {
                allowed=allowedVal;
                session=sessionVar;
                exportable=exportableVar;

            } 
        }
    }
}
