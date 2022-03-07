/**
 * @file common.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H

#include "return_types.h"
#include "proxy.h"




namespace ara
{
   namespace ucm
   {
      namespace pkgmgr
       {  
            class add_output
            {
                private:
                proxy* x;
                public:
                add_output(proxy* x)
                {
                     this->x = x;
                }
                
                ::ara::ucm::pkgmgr::addReturnType result;

                void operator()()
                {
                   x->SendRequest();
                }

                ~add_output(){};
            };

        }  //pkgmgr
   }  //ucm
}  //ara

#endif //ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H
