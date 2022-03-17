/**
 * @file updaterequest_proxy.h
 * @author basmala
 * @brief
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "functional"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/sm/update_request/update_request_common.hpp"

using namespace std;
namespace ara
{
    namespace sm
    {
        namespace update_request
        {
            namespace proxy
            {
                namespace methods
                {
                    using ResetMachine = ara::sm::update_request::ResetMachine;
                    using StopUpdateSession = ara::sm::update_request::StopUpdateSession;
                    using StartUpdateSession = ara::sm::update_request::StartUpdateSession;
                    using PrepareUpdate = ara::sm::update_request::PrepareUpdate;
                    using VerifyUpdate = ara::sm::update_request::VerifyUpdate;
                    using PrepareRollback = ara::sm::update_request::PrepareRollback;
                }

                class update_request_proxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    update_request_proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                    :ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                    ResetMachine(this),
                    StopUpdateSession(this),
                    StartUpdateSession(this),
                    PrepareUpdate(this),
                    VerifyUpdate(this),
                    PrepareRollback(this)
                    {}

                    // Methods
                    methods::ResetMachine ResetMachine;
                    methods::StopUpdateSession StopUpdateSession;
                    methods::StartUpdateSession StartUpdateSession;
                    methods::PrepareUpdate PrepareUpdate;
                    methods::VerifyUpdate VerifyUpdate;
                    methods::PrepareRollback PrepareRollback;

                };
            }
        }
    }
}