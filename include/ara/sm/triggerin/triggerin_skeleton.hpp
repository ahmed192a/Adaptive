#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_skeleton.hpp"

namespace ara
{
    namespace sm
    {
        namespace triggerin
        {
            namespace proxy_skeleton
            {

                namespace fields
                {
                    // using Trigger=int;
                    // getter  ,  setter ,  notifier
                    using Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::TriggerIn, false, true, false>::type;
                }
                class Trigger_In_Skeleton
                {
                public:
                    Trigger_In_Skeleton(
                        // ara::com::InstanceIdentifier instance,
                        // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent){}
                    
                        // Fields
                        Trigger_In_Skeleton(ara::com::proxy_skeleton::Skeleton::ServiceSkeleton::SP_Handle skeleton_handle);
                        ~Trigger_In_Skeleton();
                        // Fields
                        fields::Trigger trigger;
                    
                };
            }
        }
    }
}