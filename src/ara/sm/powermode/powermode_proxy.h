/**
 * @file powermode_proxy.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ara/com/proxy_skeleton/proxy/field.h"
#include "ara/com/proxy_skeleton/proxy/service_proxy.h"
#include "powermode_common.h"

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
                    PowerMode(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                        MessagePowerMode(this),
                        EventPowerMode(this)
                    {
                    }
                    ~PowerMode();

                    ara::sm::powermode::proxy::methods::MessagePowerMode MessagePowerMode;
                    ara::sm::powermode::proxy::methods::MessagePowerMode EventPowerMode;
                };
            }
        }
    }
}
