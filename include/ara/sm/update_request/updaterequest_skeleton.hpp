/**
 * @file updaterequest_skeleton.h
 * @author basmala
 * @brief
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_SM_UPDATEREQUEST_SKELETON_H_
#define ARA_SM_UPDATEREQUEST_SKELETON_H_

#include <unistd.h>
#include "functional"
#include <iostream>
#include <string.h>
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"

#include "ara/sm/update_request/update_request_return_types.hpp"

namespace ara
{
    namespace sm
    {
        namespace update_request
        {
            namespace skeleton
            {

                /// class update_request_Skeleton
                class update_request_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    struct sockaddr_in cliaddr;
                    ara::com::InstanceIdentifier serviceid;

                public:
                    update_request_Skeleton(
                        ara::com::InstanceIdentifier instance, 
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
                        : ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid,instance,skeleton_handle),
                        serviceid(43)

                    {
                    }

                    // Methods
                    std::future<ara::sm::update_request::ResetMachineOutput>  ResetMachine();
                    std::future<void> StopUpdateSession();
                    std::future<ara::sm::update_request::StartUpdateSessionOutput> StartUpdateSession();
                    std::future<ara::sm::update_request::PrepareUpdateOutput> PrepareUpdate();
                    std::future<ara::sm::update_request::VerifyUpdateOutput> VerifyUpdate();
                    std::future<ara::sm::update_request::PrepareRollbackOutput> PrepareRollback();

                    
                    void skeleton::method_dispatch(std::vector<uint8_t>& message, Socket& cserver)
                   {
                        ara::com::Deserializer dser;
                        int methodID = dser.deserialize<int>(message,0);
                        cout<<"\t[SERVER] Dispatch " << methodID << endl;
                        std::vector<uint8_t> msg;
                        msg.insert(msg.begin(), message.begin()+sizeof(int), message.end());


                        if (methodID == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::ResetMachine, msg, cserver);
                        }
                        else if (methodID == 1)
                        {
                            HandleCall(*this, &update_request_Skeleton::StopUpdateSession, msg, cserver);
                        }
                        else if (methodID == 2)
                        {
                            HandleCall(*this, &update_request_Skeleton::StartUpdateSession, msg, cserver);
                        }
                        else if (methodID == 3)
                        {
                            HandleCall(*this, &update_request_Skeleton::PrepareUpdate, msg, cserver);
                        }
                        else if (methodID == 4)
                        {
                            HandleCall(*this, &update_request_Skeleton::VerifyUpdate, msg, cserver);
                        }
                        else if (methodID == 5)
                        {
                            HandleCall(*this, &update_request_Skeleton::PrepareRollback, msg, cserver);
                        }
                        else
                        {
                            int result = -1;
                            cserver.SendServer(&result, sizeof(int));
                            cserver.ClientClose();
                        }
                   }
                };
            }
        }
    }
}
#endif // ARA_SM_UPDATEREQUEST_SKELETON_H_