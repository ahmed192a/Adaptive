#include "ara/com/proxy_skeleton/proxy/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"


namespace ara
{
    namespace sm
    {
        namespace triggerout
        {
            namespace proxy
            {
                namespace events
                {
                }
                namespace fields
                {
                   // using notifier = int;
                    // getter  ,  setter ,  notifier
                   using Notifier = ara::com::proxy_skeleton::proxy::FieldType<::ara::sm::TriggerOut, true, false, true>::type;
                }
                class Trigger_Out_Proxy
                {
                public:
                    // Fields
                        Trigger_Out_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle);
                        ~Trigger_Out_Proxy();   
                        // Fields
                         fields::Notifier notifier;  
                };
            }
        }
    }
}
