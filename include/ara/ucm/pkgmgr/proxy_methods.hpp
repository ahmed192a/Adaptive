/**
 * @file proxy_methods.hpp
 * @author Sarah Mohamed
 * @brief proxy methods namespace
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROXY_METHODS_HPP
#define PROXY_METHODS_HPP

#include <bits/stdc++.h>
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "ucm_return_types.hpp"
#include "ucm_types.hpp"

using namespace ara::ucm::pkgmgr::PackageManagement;

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace proxy
            {
                namespace methods
                {
                    class Activate
                    {
                    private:
                        const std::string methodName_ = "Activate";

                    public:
                        Activate();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class Cancel
                    {
                    private:
                        const std::string methodName_ = "Cancel";

                    public:
                        Cancel();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class DeleteTransfer
                    {
                    private:
                        const std::string methodName_ = "DeleteTransfer";

                    public:
                        DeleteTransfer();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class Finish
                    {
                    private:
                        const std::string methodName_ = "Finish";

                    public:
                        Finish();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetHistory
                    {
                    private:
                        const std::string methodName_ = "GetHistory";

                    public:
                        GetHistory();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetId
                    {
                    private:
                        const std::string methodName_ = "GetId";

                    public:
                        GetId();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetSwClusterChangeInfo
                    {
                    private:
                        const std::string methodName_ = "GetSwClusterChangeInfo";

                    public:
                        GetSwClusterChangeInfo();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetSwClusterDescription
                    {
                    private:
                        const std::string methodName_ = "GetSwClusterDescription";

                    public:
                        GetSwClusterDescription();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetSwClusterInfo
                    {
                    private:
                        const std::string methodName_ = "GetSwClusterInfo";

                    public:
                        GetSwClusterInfo();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetSwPackages
                    {
                    private:
                        const std::string methodName_ = "GetSwPackages";

                    public:
                        GetSwPackages();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class GetSwProcessProgress
                    {
                    private:
                        const std::string methodName_ = "GetSwProcessProgress";

                    public:
                        GetSwProcessProgress();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class ProcessSwPackage
                    {
                    private:
                        const std::string methodName_ = "ProcessSwPackage";

                    public:
                        ProcessSwPackage();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class RevertProcessedSwPackages
                    {
                    private:
                        const std::string methodName_ = "RevertProcessedSwPackages";

                    public:
                        RevertProcessedSwPackages();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class Rollback
                    {
                    private:
                        const std::string methodName_ = "Rollback";

                    public:
                        Rollback();

                        const std::string getMethodName();

                        uint64_t operator()(uint64_t size);
                    };
                    class TransferData
                    {
                    private:
                        const std::string methodName_ = "TransferData";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid =8;
                    public:
                        TransferData(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        template<std::size_t N>
                        TransferDataOutput operator()(TransferIdType id, ByteVectorType data, uint64_t blockCounter)
                        {
                            auto I = std::integer_sequence<std::size_t, N>();
                            return send(id, data, blockCounter, std::make_index_sequence<N>{});
                        }
                        template<std::size_t...index>
                        TransferDataOutput send(TransferIdType id, ByteVectorType data, uint64_t blockCounter, std::index_sequence<index...>)
                        {
                            TransferDataOutput res = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>(methodid, id, blockCounter,data[index]...);
                            return res;
                        }
                    };
                    class TransferExit
                    {
                    private:
                        const std::string methodName_ = "TransferExit";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid =9;

                    public:
                        TransferExit(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        TransferExitOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                        {
                            TransferExitOutput res = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput>(methodid, id);
                            return res;
                        }
                    };
                    class TransferStart
                    {
                    private:
                        const std::string methodName_ = "TransferStart";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid =7;
                    public:
                        TransferStart(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        TransferStartOutput operator()(uint64_t size)
                        {
                            TransferStartOutput res = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>(methodid, size);
                            return res;
                        }

                    };
                }

            }
        }
    }
}

#endif