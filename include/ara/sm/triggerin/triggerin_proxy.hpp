#include "ara/com/proxy_skeleton/proxy/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"

namespace ara
{
    namespace sm
    {
        namespace triggerin
        {
            namespace proxy
            {
                using TriggerInType = int;
                namespace fields
                {
                    // using Trigger = int;
                    // using Trigger = ara::com::proxy_skeleton::proxy::Field<int>;
                    using Trigger = ara::com::proxy_skeleton::proxy::FieldType<ara::sm::triggerin::proxy::TriggerInType, true, true, true>::type;
                }
                class Trigger_In_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    Trigger_In_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                          trigger(this, "trigger", 0)
                    {
                    }
                    ~Trigger_In_Proxy();
                    // Fields
                    fields::Trigger trigger;
                };
            }
        }
    }
}
