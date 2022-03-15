/**
 * @file triggerinout_proxy.hpp
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
        namespace triggerinout
        {
            namespace proxy
            {
                using TriggerInOutType = int;
                namespace fields
                {
                    // getter  ,  setter ,  notifier
                    using Notifier = ara::com::proxy_skeleton::proxy::FieldType<TriggerInOutType, true, true, true>::type;
                    using Trigger = ara::com::proxy_skeleton::proxy::FieldType<TriggerInOutType, true, true, true>::type;
                }

                class Trigger_InOut_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    Trigger_InOut_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                          Notifier(this, "Notifier", 0),
                          Trigger(this, "Trigger", 1)
                    {
                    }
                    ~Trigger_InOut_Proxy();
                    fields::Notifier Notifier;
                    fields::Trigger Trigger;
                };
            }
        }
    }
}