/**
 * @file powermode_common.hpp
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

#include "string"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "powermode_return_types.hpp"

namespace ara
{
    namespace sm
    {
        namespace powermode
        {
            namespace proxy
            {
                namespace methods
                {
                    class MessagePowerMode
                    {
                    private:
                        const std::string methodName_ = "MessagePowerMode";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 0;

                    public:
                        MessagePowerMode(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        MessagePowermodeOutput operator()()
                        {
                            return service_proxy->SendRequest<ara::sm::powermode::MessagePowermodeOutput>(methodid);
                        }
                    };

                    class EventPowerMode
                    {
                    private:
                        const std::string methodName_ = "EventPowerMode";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 1;

                    public:
                        EventPowerMode(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        EventPowermodeOutput operator()()
                        {
                            return service_proxy->SendRequest<ara::sm::powermode::EventPowermodeOutput>(methodid);
                        }
                    };
                }
            }

        } // namespace powermode

    } // namespace sm

} // namespace ara

#endif