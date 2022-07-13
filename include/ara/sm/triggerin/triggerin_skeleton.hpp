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
#ifndef SM_TRIGGERIN_SKELETON_H_
#define SM_TRIGGERIN_SKELETON_H_
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
                    using UCM_Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::triggerin::UCM_State, true, true, true>::type;
                    using OTA_Trigger = ara::com::proxy_skeleton::skeleton::FieldType<ara::sm::triggerin::OTA_State, true, true, true>::type;
                }
                
                class Trigger_In_UCM_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    ara::com::proxy_skeleton::ServiceId serviceid;

                public:

                    Trigger_In_UCM_Skeleton(
                        ara::com::InstanceIdentifier instance,
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle) : serviceid(55),
                                                                                                          ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                                                                                                          trigger(this, "trigger", 0)
                    {
                    }
                    ~Trigger_In_UCM_Skeleton(){};
                    const ara::com::proxy_skeleton::ServiceId GetServiceId()
                    {
                        return serviceid;
                    }
                    // Fields
                    fields::UCM_Trigger trigger;

                    void field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;
                        // int methodID = dser.deserialize<int>(message,0);

                        int event_id = message.MessageId().method_id & 0x7FFF;
                        switch (event_id)
                        {
                        case 0:
                            if(message.Length() > 16){
                                trigger.HandleSet(message, cserver);
                            }
                            else{
                                trigger.HandleGet(message, cserver);
                            }
                            // Trigger.HandleCall(message, cserver);
                            break;
                        default:
                            NoMethodHandler(message.MessageId().method_id, cserver);
                            // cserver.Send(&result2, sizeof(int));
                            // cserver.CloseSocket();

                            break;
                        }
                    }
                };
                class Trigger_In_OTA_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    ara::com::proxy_skeleton::ServiceId serviceid;

                public:

                    Trigger_In_OTA_Skeleton(
                        ara::com::InstanceIdentifier instance,
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle) : serviceid(56),
                                                                                                          ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
                                                                                                          trigger(this, "trigger", 0)
                    {
                    }
                    ~Trigger_In_OTA_Skeleton(){};
                    const ara::com::proxy_skeleton::ServiceId GetServiceId()
                    {
                        return serviceid;
                    }


                    // Fields
                    fields::OTA_Trigger trigger;

                    void field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;
                        // int methodID = dser.deserialize<int>(message,0);

                        int event_id = message.MessageId().method_id & 0x7FFF;
                        switch (event_id)
                        {
                        case 0:
                            if(message.Length() > 16){
                                trigger.HandleSet(message, cserver);
                            }
                            else{
                                trigger.HandleGet(message, cserver);
                            }
                            // Trigger.HandleCall(message, cserver);
                            break;
                        default:
                            NoMethodHandler(message.MessageId().method_id, cserver);
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
#endif // SM_TRIGGERIN_SKELETON_H_