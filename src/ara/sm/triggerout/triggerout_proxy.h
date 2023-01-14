#include "ara/com/proxy_skeleton/proxy/field.h"
#include "ara/com/proxy_skeleton/proxy/service_proxy.h"


namespace ara
{
    namespace sm
    {
        namespace triggerout
        {
            namespace proxy
            {
                using TriggerOutType = int;
                namespace events
                {
                }
                namespace fields
                {
                    // getter  ,  setter ,  notifier
                   using Notifier = ara::com::proxy_skeleton::proxy::FieldType<TriggerOutType, true, true, true>::type;
                }
                class Trigger_Out_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    // Fields
                        Trigger_Out_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                        Notifier(this, "Notifier", 0)
                        {

                        }
                        ~Trigger_Out_Proxy();   
                        // Fields
                        fields::Notifier Notifier;  
                };
            }
        }
    }
}
