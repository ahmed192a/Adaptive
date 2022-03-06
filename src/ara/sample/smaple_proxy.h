#ifndef ARA_COM_SAMPLE_RADAR_PROXY_H_
#define ARA_COM_SAMPLE_RADAR_PROXY_H_
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
            namespace proxy
            {

                namespace events
                {
                    using Break_Event_e = ara::com::proxy_skeleton::proxy::Event<::ara::com::sample::break_event>;
                } // namespace events

                namespace fields
                {
                    // has getter , doesn't has setter , has notifier
                    using Update_Rate_f = ara::com::proxy_skeleton::proxy::FieldType<::ara::com::sample::update_rate, true, false, true>::type; 
                } // namespace fields

                namespace methods
                {
                    using Adjust = ara::com::proxy_skeleton::proxy::Method<ara::com::sample::Radar::Adjust(uint32_t target_position)>;
                } // namespace methods
                

                class Radar_Proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                private:
                    /* data */
                public:
                    using HandleType = ara::com::proxy_skeleton::proxy::ServiceProxy::HandleType;

                    Radar_Proxy(HandleType handle)
                        : ara::com::proxy_skeleton::proxy::ServiceProxy("Radar_Proxy", handle),
                        break_event(this,"break_event"),
                        update_rate(this,"update_rate"),
                        Adjust(this,"Adjsut")
                        {}
                    ~Radar_Proxy();

                    // events
                    events::Break_Event_e break_event;

                    // fields
                    fields::Update_Rate_f update_rate;

                    // methods
                    methods::Adjust Adjust;
                };
            } // namespace proxy

        } // namespace sample

    } // namespace com

} // namespace ara
#endif //ARA_COM_SAMPLE_RADAR_PROXY_H_
