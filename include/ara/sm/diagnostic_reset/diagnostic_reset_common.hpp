/**
 * @file diagnostic_reset_common.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "ara/sm/diagnostic_reset/diagnostic_reset_return_types.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
namespace ara
{
    namespace sm
    {
        namespace diagnostic_reset
        {
            class message_diagnostic
            {
            
            private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 0;
            public:
            message_diagnostic(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            MessageDiagnosticOutput operator()()
            {
                // return app error krejected
                return service_proxy_ptr->SendRequest<MessageDiagnosticOutput>(methodid);
            }
            };
            class event_diagnostic
            {
                
              private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 1;
            public:
            event_diagnostic(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            EventDiagnosticOutput operator()()
            {
                // return app error krejected
                return service_proxy_ptr->SendRequest<EventDiagnosticOutput>(methodid);
            }
            };
        } // namespace DiagnosticReset

    } // namespace sm

} // namespace ara

#endif