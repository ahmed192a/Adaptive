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
                namespace fields
                {
                   // using Trigger = int;
                  // using Trigger = ara::com::proxy_skeleton::proxy::Field<int>;
                   using Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::TriggerIn, false, true, false>::type;
                }
                class Trigger_In_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                        Trigger_In_Proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle);
                        ~Trigger_In_Proxy();   
                        // Fields
                         fields::Trigger trigger;            
                };
            }
        }
    }
}
