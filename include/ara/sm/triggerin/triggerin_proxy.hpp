#ifndef SM_TRIGGERIN_PROXY_H_
#define SM_TRIGGERIN_PROXY_H_


#include "ara/com/proxy_skeleton/proxy/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "ara/sm/triggerin/triggerin_types.hpp"

namespace ara
{
    namespace sm
    {
        namespace triggerin
        {
            namespace proxy
            {
                namespace fields
                {

                    using UCM_Trigger = ara::com::proxy_skeleton::proxy::FieldType<ara::sm::triggerin::UCM_State, true, true, true>::type;
                    using OTA_Trigger = ara::com::proxy_skeleton::proxy::FieldType<ara::sm::triggerin::OTA_State, true, true, true>::type;
                }
                class Trigger_In_UCM_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    // using Trigger_t = ara::com::proxy_skeleton::proxy::FieldType<T, true, true, true>::type;
                    Trigger_In_UCM_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                          trigger(this, "trigger", 0)
                    {
                    }
                    ~Trigger_In_UCM_Proxy(){};
                    // Fields
                    fields::UCM_Trigger trigger;
                };
                class Trigger_In_OTA_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    // using Trigger_t = ara::com::proxy_skeleton::proxy::FieldType<T, true, true, true>::type;
                    Trigger_In_OTA_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                          trigger(this, "trigger", 0)
                    {
                    }
                    ~Trigger_In_OTA_Proxy(){};
                    // Fields
                    fields::OTA_Trigger trigger;
                };
            }
        }
    }
}
#endif // SM_TRIGGERIN_PROXY_H_