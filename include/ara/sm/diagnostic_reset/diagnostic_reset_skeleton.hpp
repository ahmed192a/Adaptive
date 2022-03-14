/**
 * @file diagnostic_reset_skeleton.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_skeleton.hpp"


namespace ara
{
    namespace sm
    {
        namespace diagnostic_reset
        {
            namespace skeleton
            {
                class PowerMode
                {
                public:
                    diagnostic_reset(
                        // ara::com::InstanceIdentifier instance,
                        // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent){}
                    
                        diagnostic_reset(ara::com::proxy_skeleton::Skeleton::ServiceSkeleton::SP_Handle skeleton_handle);
                        ~diagnostic_reset();
                    /*sends DiagnosticResetMsg defined in 9.1 Type definition to all Processes in a SoftwareCluster.*/
                    ara::sm::diagnostic_reset::skeleton::MessageDiagnosticOutput message(DiagnosticResetMsg msg);
                    /*All Processes which got a DiagnosticReset request sends this as answer to State Management*/
                    ara::sm::diagnostic_reset::skeleton::EventDiagnosticOutput event(DiagnosticResetRespMsg respMsg);
                };
            }
        }
    }
}