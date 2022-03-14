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
                namespace fields
                {
                    // getter  ,  setter ,  notifier
                   using Notifier = ara::com::proxy_skeleton::proxy::FieldType<ara::sm::TriggerInOut, true, false, true>::type;
                   using Trigger = ara::com::proxy_skeleton::proxy::FieldType<ara::sm::TriggerInOut, false, true, false>::type;
                }

                class Trigger_InOut_Proxy
                {
                public:
                    /* explicit TriggerInOutProxy()
                          Trigger_Out_Skeleton(
                         ara::com::InstanceIdentifier instance,
                         ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
                         // , notifier(this, "notifier")
                            ,trigger(this,"trigger")

                     )
                     */
                    Trigger_InOut_Proxy();
                    ~Trigger_InOut_Proxy();
                    fields::Notifier notifier;  
                    fields::Trigger trigger; 
                        
 
    
                };
            }
        }
    }
}