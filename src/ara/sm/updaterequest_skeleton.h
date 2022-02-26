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

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "functional"
#include "CServer.h"
#include <vector>
#include "proxy_skeleton/skeleton/service_skeleton.h"
#include "proxy_skeleton/definitions.h"
using namespace std;

namespace ara
{
    namespace sm
    {
        namespace update_request
        {
            namespace proxy_skeleton
            {
                namespace events
                {
                    //define events here
                }
                namespace fields
                {
                    //define fields here
                }
                namespace methods
                {
                    //define methods here

                    // using ResetMachine = int;
                    // using StopUpdateSession = int;
                    // using StartUpdateSession = int;
                    // using PrepareUpdate = int;
                    // using VerifyUpdate = int;
                    // using PrepareRollback = int;
                }

                struct SD_data
                {
                    int service_id;
                    int process_id;
                    int port_number;
                    bool message_type;
                };

                // class Service_skeleton;

                class update_request_Skeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton

                {
                private:
                    /* data */
                    int portNumber;
                    int service_id;
                    int service_descovery_port_number;
                    CServer s1;
                    struct sockaddr_in cliaddr;

                public:
                    update_request_Skeleton(
                        ara::com::InstanceIdentifier instance,
                        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
                        : ara::com::proxy_skeleton::skeleton::ServiceSkeleton("update_request_Skeleton", instance, mode),
                          s1(SOCK_DGRAM)
                    {
                    }

                    // Events

                    // Fields

                    // Methods
                    virtual void ResetMachine();
                    virtual void StopUpdateSession();
                    virtual void StartUpdateSession();
                    virtual void PrepareUpdate();
                    virtual void VerifyUpdate();
                    virtual void PrepareRollback();

                    using FunctionGroupNameType = std::string;

                    // [SWS_SM_91018]
                    /*
                     * Name        : FunctionGroupListType
                     * Subelements : FunctionGroupNameType
                     * Description : A list of FunctionGroups.
                     */
                    using FunctionGroupListType = std::vector<FunctionGroupNameType>;

                    void start_service()
                    {
                        // s1(SOCK_DGRAM);
                        this->s1.OpenSocket(portNumber);
                        this->s1.BindServer();
                        struct SD_data service = {service_id, getpid(), portNumber, true};

                        // struct sockaddr_in  cliaddr;
                        this->cliaddr.sin_family = AF_INET; // IPv4
                        this->cliaddr.sin_addr.s_addr = INADDR_ANY;
                        this->cliaddr.sin_port = htons(service_descovery_port_number);

                        this->s1.UDPSendTo((const struct SD_data *)&service, sizeof(struct SD_data), (const struct sockaddr *)&this->cliaddr);

                        // this->s1.CloseSocket();
                    }

                    void StopOfferService()
                    {
                        // CServer s1(SOCK_DGRAM);
                        // s1.OpenSocket(portNumber);
                        // s1.BindServer();
                        struct SD_data service = {service_id, getpid(), portNumber, false};

                        // struct sockaddr_in  cliaddr;
                        // cliaddr.sin_family = AF_INET; // IPv4
                        // cliaddr.sin_addr.s_addr = INADDR_ANY;
                        // cliaddr.sin_addr.s_addr = INADDR_ANY;
                        // cliaddr.sin_port = htons(service_descovery_port_number);

                        this->s1.UDPSendTo((const struct SD_data *)&service, sizeof(struct SD_data), (const struct sockaddr *)&this->cliaddr);
                        int x;
                        socklen_t len = sizeof(this->cliaddr);
                        // (struct sockaddr *) &cliaddr
                        this->s1.UDPRecFrom(&x, sizeof(int), (struct sockaddr *)&this->cliaddr, &len);
                        this->s1.CloseSocket();
                    }

                    void method_dispatch(struct ara::com::proxy_skeleton::Message &message, CServer &cserver)
                    {
                        cout << "Dispatch " << message.method_name << endl;
                        if (strcmp(message.method_name, "ResetMachine") == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::ResetMachine, message, cserver);
                        }
                        else if (strcmp(message.method_name, "StopUpdateSession") == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::StopUpdateSession, message, cserver);
                        }
                        else if (strcmp(message.method_name, "StartUpdateSession") == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::StartUpdateSession, message, cserver);
                        }
                        else if (strcmp(message.method_name, "PrepareUpdate") == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::PrepareUpdate, message, cserver);
                        }
                        else if (strcmp(message.method_name, "VerifyUpdate") == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::VerifyUpdate, message, cserver);
                        }
                        else if (strcmp(message.method_name, "PrepareRollback") == 0)
                        {
                            HandleCall(*this, &update_request_Skeleton::PrepareRollback, message, cserver);
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