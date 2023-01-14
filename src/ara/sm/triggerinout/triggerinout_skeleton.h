/**
 * @file triggerinout_skeleton.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ara/com/proxy_skeleton/skeleton/field.h"
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.h"
#include "ara/com/proxy_skeleton/definitions.h"
#include "ara/sm/triggerinout/triggerinout_types.h"
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
                    namespace events
                    {

                    }
                    namespace fields
                    {
                        // getter  ,  setter ,  notifier
                        using Notifier = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::triggerinout::TriggerInOutType, true, true, true>::type;
                        using Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::triggerinout::TriggerInOutType, true, true, true>::type;
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


                        void field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                        {
                            ara::com::Deserializer dser;

                            int event_id = message.MessageId().method_id & 0x7FFF;
                            switch (event_id)
                            {
                            case 0:
                                if(message.Length() > 16){
                                    Notifier.HandleGet(message, cserver);
                                }
                                else{
                                    Notifier.HandleSet(message, cserver);
                                }
                                // Notifier.HandleCall(message, cserver);
                                break;
                            case 1:
                                if(message.Length() > 16){
                                    Trigger.HandleGet(message, cserver);
                                }
                                else{
                                    Trigger.HandleSet(message, cserver);
                                }
                                // Trigger.HandleCall(message, cserver);
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
}