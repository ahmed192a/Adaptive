/**
 * @file triggerout_skeleton.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "ara/sm/triggerout/triggerout_types.hpp"
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
                    //  getter  ,  setter ,  notifier
                    using Notifier = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::triggerout::TriggerOut, true, true, true>::type;
                }
                class Trigger_Out_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                public:
                    Trigger_Out_Skeleton(ara::com::InstanceIdentifier instance,
                                         ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
                        : serviceid(47), ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                          Notifier(this, "Notifier", 0)
                    {
                    }
                    ~Trigger_Out_Skeleton();

                    // Fields
                    fields::Notifier Notifier;

                    void field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;
                        // int methodID = dser.deserialize<int>(message,0);

                        int event_id = message.MessageId().method_id & 0x7FFF;
                        switch (event_id)
                        {
                        case 2:
                            if(message.Length() > 16){
                                Notifier.HandleGet(message, cserver);
                            }
                            else{
                                Notifier.HandleSet(message, cserver);
                            }
                            // Notifier.HandleCall(message, cserver);
                            break;
                        default:
                            // cserver.Send(&result2, sizeof(int));
                            // cserver.CloseSocket();

                            break;
                        }
                    }

                private:
                    ara::com::InstanceIdentifier serviceid;
                };
            }

        }
    }
}
