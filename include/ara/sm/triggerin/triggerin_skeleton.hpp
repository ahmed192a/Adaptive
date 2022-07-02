/**
 * @file triggerin_skeleton.hpp
 * @author
 * @brief
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "ara/sm/triggerin/triggerin_types.hpp"

namespace ara
{
    namespace sm
    {
        namespace triggerin
        {
            namespace skeleton
            {
                namespace fields
                {
                    /**
                     * @todo type: project specific
                     *
                     */
                    using Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::triggerin::TriggerInType, true, true, true>::type;
                }
                template <typename T>
                class Trigger_In_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    ara::com::InstanceIdentifier serviceid;

                public:
                    using Trigger_t = ara::com::proxy_skeleton::skeleton::FieldType<T, true, true, true>::type;

                    Trigger_In_Skeleton(
                        ara::com::InstanceIdentifier instance,
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle) : serviceid(55),
                                                                                                          ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                                                                                                          Trigger(this, "trigger", 0)
                    {
                    }
                    ~Trigger_In_Skeleton();

                    // Fields
                    // fields::Trigger Trigger;
                    Trigger_t Trigger;

                    void field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;
                        // int methodID = dser.deserialize<int>(message,0);

                        int event_id = message.MessageId().method_id & 0x7FFF;
                        switch (event_id)
                        {
                        case 0:
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
                };
            }
        }
    }
}