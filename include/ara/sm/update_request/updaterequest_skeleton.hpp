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

                    
                    void method_dispatch(ara::com::SOMEIP_MESSAGE::Message&message, Socket& cserver)
                   {
                        ara::com::Deserializer dser;
                        // int methodID = dser.deserialize<int>(message,0);
                        int methodID = message.MessageId().method_id;
                        cout<<"\t[SERVER] Dispatch " << methodID << endl;
                        // std::vector<uint8_t> msg;
                        // msg.insert(msg.begin(), message.begin()+sizeof(int), message.end());

                        switch (methodID)
                        {
                        case 0:
                            HandleCall(*this,&update_request_Skeleton::ResetMachine,message,cserver);
                            break;
                        case 1:
                            HandleCall(*this,&update_request_Skeleton::StopUpdateSession,message,cserver);
                            break;
                        case 2:
                            HandleCall(*this,&update_request_Skeleton::StartUpdateSession,message,cserver);
                            break;
                        case 3:
                            HandleCall(*this,&update_request_Skeleton::PrepareUpdate,message,cserver);
                            break;
                        case 4:
                            HandleCall(*this,&update_request_Skeleton::VerifyUpdate,message,cserver);
                            break;
                        case 5:               
                            HandleCall(*this,&update_request_Skeleton::PrepareRollback,message,cserver);
                            break;
                        default:
                            break;
                        }
                   }
                };
            }
        }
    }
}
#endif // ARA_SM_UPDATEREQUEST_SKELETON_H_