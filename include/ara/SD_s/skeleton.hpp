/**
 * @file skeleton.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/com/ipc/server/socket_Server.hpp"
#include <unistd.h>
#include "functional"
#include <iostream>
#include <string.h>
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
using C_Info = ara::com::proxy_skeleton::C_Info;

#define portNumber 5365
#define service_descovery_port_number 1690

namespace event
{
    using event = ara::com::proxy_skeleton::skeleton::Event<int>;
} // namespace event

namespace field
{
    using field = ara::com::proxy_skeleton::skeleton::Field<int>;
} // namespace field

class skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
{
private:
    /* data */
    // int portNumber = 5365;
    int service_id;
    // int service_descovery_port_number = 1690;
    CServer *s1;
    struct sockaddr_in cliaddr;

public:
    event::event event1;
    event::event event2;
    field::field field1;
    skeleton(int service_id, CServer *server_udp);
    ~skeleton();
    void method_dispatch(std::vector<uint8_t> &message, Socket &cserver);
    int Add(std::vector<uint8_t> msg);
};
