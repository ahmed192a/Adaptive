/**
 * @file powermode_skeleton.hpp
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
        namespace powermode
        {
            namespace skeleton
            {

                class PowerMode
                {
                public:
                       // PowerMode(
                        // ara::com::InstanceIdentifier instance,
                        // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent){}
                    
                        powermode(ara::com::proxy_skeleton::Skeleton::ServiceSkeleton::SP_Handle skeleton_handle);
                        ~powermode();
                    /*sends PowerModeMsg defined in 9.1 Type definition to all Processes to request a PowerMode.
                     *Message to all running Processes in the system to indicate a request to enter this state.*/
                    ara::sm::powermode::skeleton::MessagePowermodeOutput message(PowerModeMsg msg);
                    /*ResponseMessage from a Processes which received PowerMode request from State Management.*/ 
                    ara::sm::powermode::skeleton::EventPowermodeOutput event(PowerModeRespMsg respMsg);
                };
            }
        }
    }
}