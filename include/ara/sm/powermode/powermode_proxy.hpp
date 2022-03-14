/**
 * @file powermode_proxy.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ara/com/proxy_skeleton/proxy/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"


namespace ara
{
    namespace sm
    {
        namespace powermode
        {
            namespace proxy
            {

                class PowerMode : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                        powermode(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle);
                        ~powermode();   
          
                };
            }
        }
    }
}
