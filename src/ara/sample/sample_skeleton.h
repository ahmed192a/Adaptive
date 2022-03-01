#ifndef ARA_COM_SAMPLE_RADAR_SKELETON_H_
#define ARA_COM_SAMPLE_RADAR_SKELETON_H_
// fixed headers
#include <string.h>
#include "core/future.h"
#include "com/proxy_skeleton/skeleton/service_skeleton.h"
#include "com/proxy_skeleton/definitions.h"

// header from xml
#include "stdtypes.h"

namespace ara
{
    namespace com
    {
        namespace sample
        {
            namespace skeleton
            {

                namespace events
                {
                    using Break_Event_e = ara::com::proxy_skeleton::skeleton::Event<::ara::com::sample::break_event>;
                } // namespace events

                namespace fields
                {
                    // has getter , has setter , doesn't has notifier
                    using Update_Rate_f = ara::com::proxy_skeleton::skeleton::FieldType<::ara::com::smaple::update_rate, true, false, true>::type; 
                } // namespace fields

                class Radar_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    /* data */
                public:
                    Radar_Skeleton(
                        ara::com::InstanceIdentifier instance,
                        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
                        : ara::com::proxy_skeleton::skeleton::ServiceSkeleton("Radar_Skeleton", instance, mode),
                        break_event(this,"break_event"),
                        update_rate(this,"update_rate")
                        {}
                    ~Radar_Skeleton();

                    // events
                    events::Break_Event_e break_event;

                    // fields
                    fields::Update_Rate_f update_rate;

                    // methods
                    ara::core::Future<void> Adjust(uint32_t target_position);
                };
            } // namespace skeleton

        } // namespace sample

    } // namespace com

} // namespace ara
#endif //ARA_COM_SAMPLE_RADAR_SKELETON_H_
