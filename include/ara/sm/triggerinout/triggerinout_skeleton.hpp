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

#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"

namespace ara
{
    namespace sm
    {
        namespace triggerinout
        {
            namespace proxy_skeleton
            {
                namespace skeleton
                {
                    using TriggerInOutType = int;
                    namespace events
                    {

                    }
                    namespace fields
                    {
                        // getter  ,  setter ,  notifier
                        using Notifier = ara::com::proxy_skeleton::skeleton::FieldType<TriggerInOutType, true, true, true>::type;
                        using Trigger = ara::com::proxy_skeleton::skeleton::FieldType<TriggerInOutType, true, true, true>::type;
                    }

                    class Trigger_InOut_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                    {
                    public:
                        Trigger_InOut_Skeleton(ara::com::InstanceIdentifier instance,
                                             ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
                            : serviceid(49), ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                            Notifier(this, "Notifier", 0),
                            Trigger(this, "Trigger", 1)
                        {
                        }
                        ~Trigger_InOut_Skeleton();
                        fields::Notifier Notifier;
                        fields::Trigger Trigger;

                    private:
                        ara::com::InstanceIdentifier serviceid;
                    };
                }
            }
        }
    }
}