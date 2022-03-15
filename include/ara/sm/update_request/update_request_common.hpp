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
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 1;
            public:
            ResetMahcine(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            ResetMachineOutput operator()()
            {
                // return app error krejected
                return service_proxy_ptr->SendRequest<ResetMachineOutput>(methodid);

            }
            
            };
            class StopUpdateSession
            {
            private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 2;
            public:
            StopUpdateSession(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            void operator()()
            {
                // fire and forget
                return service_proxy_ptr->SendRequest<void>(methodid);
            }
            };
            class RequestUpdateSession
            {
            private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 3;
            public:
            RequestUpdateSession(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            RequestUpdateSessionOutput operator()()
            {
                // return app error krejected
                return service_proxy_ptr->SendRequest<RequestUpdateSessionOutput>(methodid);
            }
            };
            class PrepareUpdate
            {
            private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 4;
            public:
            PrepareUpdate(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            PrepareUpdateOutput operator()(FunctionGroupListType FunctionGroupList)
            {
                // under development
                // return app error krejected, kprepared_failed
                //return service_proxy_ptr->SendRequest<PrepareUpdateOutput>(methodid,FunctionGroupList);
            }
            };
            class VerifyUpdate
            {
            private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 5;
            public:
            VerifyUpdate(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            VerifyUpdateOutput operator()(FunctionGroupListType FunctionGroupList)
            {
                // under development
                // return app error krejected, kverify_failed
                //return service_proxy_ptr->SendRequest<VerifyUpdateOutput>(methodid,FunctionGroupList);
            }
            };
            class PrepareRollback
            {
            private:
            ara::com::proxy_skeleton::proxy::ServiceProxy * service_proxy_ptr;
            const int methodid = 6;
            public:
            PrepareRollback(ara::com::proxy_skeleton::proxy::ServiceProxy * service):service_proxy_ptr{service}
            {}
            PrepareRollbackOutput operator()(FunctionGroupListType FunctionGroupList)
            {
                // under development
                // return app error krejected, krollback_failed
                //return service_proxy_ptr->SendRequest<PrepareRollbackOutput>(methodid,FunctionGroupList);
            }
            };
        } // namespace update_request

    } // namespace sm

} // namespace ara

#endif