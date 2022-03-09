/**
 * @file proxy.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "ara/com/proxy_skeleton/proxy/field.hpp"

// later this file will be UCM Proxy
namespace saam
{
    namespace events
    {
        using EV1 = ara::com::proxy_skeleton::proxy::Event<int>;
    } // namespace events

    namespace fields
    {
        using FD1 = ara::com::proxy_skeleton::proxy::Field<int>;
    } // namespace events

    class proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
    {
    private:
        /* data */

    public:
        events::EV1 ev1;
        // fields::FD1 fd1;
        proxy();

        int Add(int x, int y)
        {
            return SendRequest(0,x,y);
        }

        ~proxy();
    };

}