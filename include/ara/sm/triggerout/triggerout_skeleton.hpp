/**
 * @file triggerout_skeleton.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ara/com/proxy_skeleton/proxy/field.hpp"
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"

namespace ara
{
    namespace sm
    {
        namespace triggerout
        {
            namespace skeleton
            {
                namespace events
                {

                }
                namespace fields
                {
                    // using notifier=int;
                    //  getter  ,  setter ,  notifier
                    using Notifier = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::TriggerOut, true, true, true>::type;

                }
                class Trigger_Out_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                public:
                    // Trigger_Out_Skeleton(
                    //     /* ara::com::InstanceIdentifier instance,
                    //      ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent*/
                    //     );
                    Trigger_Out_Skeleton(ara::com::InstanceIdentifier instance,
                                         ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
                        : serviceid(47), ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                        Notifier(this, "Notifier", 0)
                    {
                    }
                    ~Trigger_Out_Skeleton();

                    // Fields
                    fields::Notifier Notifier;

                private:
                    ara::com::InstanceIdentifier serviceid;
                };
            }

        }
    }
}
