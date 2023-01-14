/**
 * @file diagnostic_reset_skeleton.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ara/com/proxy_skeleton/skeleton/field.h"
#include "ara/com/proxy_skeleton/proxy/service_skeleton.h"

#include "ara/sm/diagnostic_reset/diagnostic_reset_return_types.h"

#include <future>

namespace ara
{
    namespace sm
    {
        namespace diagnostic_reset
        {
            namespace skeleton
            {
                class diagnostic_reset_skeleton
                {
                private:
                    struct sockaddr_in cliaddr;
                    ara::com::InstanceIdentifier serviceid;

                public:
                    diagnostic_reset(
                        ara::com::InstanceIdentifier instance,
                        ara::com::proxy_skeleton::Skeleton::ServiceSkeleton::SP_Handle skeleton_handle)
                        : ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                          serviceid(14)
                    {
                    }
                    ~diagnostic_reset();

                    /*sends DiagnosticResetMsg defined in 9.1 Type definition to all Processes in a SoftwareCluster.*/
                    std::future<ara::sm::diagnostic_reset::MessageDiagnosticOutput> message();

                    /*All Processes which got a DiagnosticReset request sends this as answer to State Management*/
                    std::future<ara::sm::diagnostic_reset::EventDiagnosticOutput> event();

                    void skeleton::method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                    {
                        int methodID = message.MessageId().method_id;
                        cout << "\t[SERVER] Dispatch " << methodID << endl;

                        switch (methodID)
                        {
                        case 0:
                            HandleCall(*this, &diagnostic_reset_skeleton::message, message, cserver);
                            break;
                        case 1:
                            HandleCall(*this, &diagnostic_reset_skeleton::event, message, cserver);
                            break;
                        default:
                            // int result = -1;
                            // cserver.SendServer(&result, sizeof(int));
                            // cserver.ClientClose();

                            break;
                        }
                    }
                };
            }
        }
    }
}