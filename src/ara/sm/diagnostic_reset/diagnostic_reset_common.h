/**
 * @file diagnostic_reset_common.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "ara/sm/diagnostic_reset/diagnostic_reset_return_types.h"
#include "ara/com/proxy_skeleton/proxy/service_proxy.h"
namespace ara
{
    namespace sm
    {
        namespace diagnostic_reset
        {
            class message_diagnostic
            {

            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 0;

            public:
                message_diagnostic(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }

                std::future<ara::sm::diagnostic_reset::MessageDiagnosticOutput> operator()()
                {

                    std::future<ara::sm::diagnostic_reset::MessageDiagnosticOutput> result = std::async([&]()
                    {

                        // add function code
                    return service_proxy_ptr->SendRequest<ara::sm::diagnostic_reset::MessageDiagnosticOutput>(methodid); 
                    });
                    // return app error krejected
                    return result;
                }
            };

            class event_diagnostic
            {

            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 1;

            public:
                event_diagnostic(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<ara::sm::diagnostic_reset::EventDiagnosticOutput> operator()()
                {
                    std::future<ara::sm::diagnostic_reset::EventDiagnosticOutput> result = std::async([&]()
                    {
                        // add function code
                       return service_proxy_ptr->SendRequest<ara::sm::diagnostic_reset::EventDiagnosticOutput>(methodid); 
                    });
                    // return app error krejected
                    return result;
                }
            };
        } // namespace DiagnosticReset

    } // namespace sm

} // namespace ara

#endif