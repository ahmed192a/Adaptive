/**
 * @file triggerinout_skeleton.hpp
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
#include "ara/com/proxy_skeleton/proxy/service_skeleton.hpp"


namespace ara
{
    namespace sm
    {
        namespace triggerinout
        {
            namespace proxy_skeleton
            {
                namespace events
                {

                }
                namespace fields
                {
                    // getter  ,  setter ,  notifier
                    using Notifier = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::TriggerInOut, true, false, true>::type;
                    using Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::TriggerInOut, false, true, false>::type;
                }

                class Trigger_InOut_Skeleton
                {
                public:
                    // Trigger_InOut_Skeleton(
                    //     /* ara::com::InstanceIdentifier instance,
                    //      ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent*/
                    // );
                    Trigger_Out_Skeleton(ara::com::proxy_skeleton::Skeleton::ServiceSkeleton::SP_Handle skeleton_handle);
                    ~Trigger_InOut_Skeleton();
                    fields::Notifier Notifier;
                    fields::Trigger Trigger;
                };
            }
        }
    }
}