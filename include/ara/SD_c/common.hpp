/**
 * @file common.hpp
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

#include "ara/SD_c/return_types.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
// #include "ara/SD_c/proxy.hpp"


namespace saam
{
    // class proxy;
    class add_output
    {
        private:
        ara::com::proxy_skeleton::proxy::ServiceProxy *px;
        int methodid =5;
        public:
        add_output(ara::com::proxy_skeleton::proxy::ServiceProxy* x)
        {
            this->px = x;
        }
        
        ::saam::addReturnType result;

        // saam::addReturnType operator()(int x, int y)
        // {
        //     result.add = px->SendRequest(0,x,y);
        //     return result;
        // }
        int operator()(int p1, int p2)
        {
            int res = px->SendRequest<int>(methodid,p1,p2);
            return res;
        }

        ~add_output(){};
    };

}  //ara

#endif //ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H
