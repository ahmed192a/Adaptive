/**
 * @file update_request_common.hpp
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
#include "ara/sm/update_request/update_request_return_types.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "future"
using namespace std;

// include the file  of the following types
// [SWS_SM_91019]
/*
 * Name        : FunctionGroupNameType
 * Kind        : STRING
 * Description : full qualified FunctionGroup shortName.
 */
using FunctionGroupNameType = std::string;

// [SWS_SM_91018]
/*
 * Name        : FunctionGroupListType
 * Kind        : VECTOR
 * Subelements : FunctionGroupNameType
 * Description : A list of FunctionGroups.
 */
using FunctionGroupListType = std::vector<FunctionGroupNameType>;
namespace ara
{
    namespace sm
    {
        namespace update_request
        {
            class ResetMachine
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 1;

            public:
                ResetMachine(ara::com::proxy_skeleton::proxy::ServiceProxy *service)
                 : service_proxy_ptr{service}
                {
                }
                
                std::future<ara::sm::update_request::ResetMachineOutput> operator()()
                {
                    std::future<ara::sm::update_request::ResetMachineOutput> result = std::async([&]()
                    {
                        // add function code
                        // return app error krejected
                       return service_proxy_ptr->SendRequest<ara::sm::update_request::ResetMachineOutput>(methodid); 
                    });
                    // return app error krejected
                    return result;
                }
            };
            class StopUpdateSession
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 2;

            public:
                StopUpdateSession(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<void> operator()()
                {
                    std::future<void> result = std::async([&]()
                    {
                        // add function code
                        // fire and forget
                       return service_proxy_ptr->SendRequest<void>(methodid); 
                    });
                    // return app error krejected
                    return result;
                }
            };
           class StartUpdateSession
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 3;
                
            public:

                StartUpdateSession(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<ara::sm::update_request::StartUpdateSessionOutput> operator()()
                {
                    std::future<ara::sm::update_request::StartUpdateSessionOutput> result = std::async([&]()
                    {
                        // add function code
                        // return app error krejected
                       return service_proxy_ptr->SendRequest<ara::sm::update_request::StartUpdateSessionOutput>(methodid); 
                    });
                    // return app error krejected
                    return result;
                }
            };
            class RequestUpdateSession
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 4;

            public:
                RequestUpdateSession(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<ara::sm::update_request::RequestUpdateSessionOutput> operator()()
                {
                    std::future<ara::sm::update_request::RequestUpdateSessionOutput> result = std::async([&]()
                    {
                        // add function code
                        // return app error krejected
                       return service_proxy_ptr->SendRequest<ara::sm::update_request::RequestUpdateSessionOutput>(methodid); 
                    });
                    
                    // return app error krejected
                    return result;
                }
            };
            class PrepareUpdate
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 5;

            public:
                PrepareUpdate(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<ara::sm::update_request::PrepareUpdateOutput> operator()(FunctionGroupListType FunctionGroupList)
                {
                    std::future<ara::sm::update_request::PrepareUpdateOutput> result = std::async([&, FunctionGroupList]()
                    {
                        ara::sm::update_request::PrepareUpdateOutput f;
                        return f;
                    // under development
                       // return app error krejected, kprepared_failed
                       //return service_proxy_ptr->SendRequest<ara::sm::update_request::PrepareUpdateOutput>(methodid,FunctionGroupList); 
                    });
                    // return app error krejected
                    return result;
                }
            };
            class VerifyUpdate
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 6;

            public:
                VerifyUpdate(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<ara::sm::update_request::VerifyUpdateOutput> operator()(FunctionGroupListType FunctionGroupList)
                {
                    std::future<ara::sm::update_request::VerifyUpdateOutput> result = std::async([&, FunctionGroupList]()
                    {
                        ara::sm::update_request::VerifyUpdateOutput f;
                        return f;
                       // under development
                       // return app error krejected, kverify_failed
                       //return service_proxy_ptr->SendRequest<ara::sm::update_request::VerifyUpdateOutput>(methodid,FunctionGroupList); 
                    });
                    return result;
                }
            };
            class PrepareRollback
            {
            private:
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy_ptr;
                const int methodid = 7;

            public:
                PrepareRollback(ara::com::proxy_skeleton::proxy::ServiceProxy *service) : service_proxy_ptr{service}
                {
                }
                std::future<ara::sm::update_request::PrepareRollbackOutput> operator()(FunctionGroupListType FunctionGroupList)
                {
                    std::future<ara::sm::update_request::PrepareRollbackOutput> result = std::async([&, FunctionGroupList]()
                    {
                        ara::sm::update_request::PrepareRollbackOutput f;
                        return f;
                       // under development
                       // return app error krejected, krollback_failed
                       //return service_proxy_ptr->SendRequest<ara::sm::update_request::PrepareRollbackOutput>(methodid,FunctionGroupList); 
                    });
                    return result;
                }
            };
        } // namespace update_request

    } // namespace sm

} // namespace ara

#endif