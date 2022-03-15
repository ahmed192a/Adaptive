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
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 21;
                    public:
                        Activate(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ActivateOutput operator()()
                        {
                            ActivateOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::ActivateOutput>(methodid);
                            return result;  
                        }
                    };
                    class Cancel
                    {
                    private:
                        const std::string methodName_ = "Cancel";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 20;
                    public:
                        Cancel(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {

                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::CancelOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                        {
                            CancelOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::CancelOutput>(methodid, id);
                            return result;            
                        }
                    };
                    class DeleteTransfer
                    {
                    private:
                        const std::string methodName_ = "DeleteTransfer";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 19;
                    public:
                        DeleteTransfer(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {

                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput operator()(TransferIdType id)
                        {
                            DeleteTransferOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput>(methodid, id);
                            return result;
                        }
                    };
                    class Finish
                    {
                    private:
                        const std::string methodName_ = "Finish";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 18;
                    public:
                        Finish(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {

                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::FinishOutput operator()()
                        {
                            FinishOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::FinishOutput>(methodid);
                            return result;
                        }
                        
                    };
                    class GetHistory
                    {
                    private:
                        const std::string methodName_ = "GetHistory";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 17;
                    public:
                        GetHistory(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {

                        }

                        const std::string getMethodName();

                        GetHistoryOutput operator()(uint64_t timestampGE, uint64_t timestampLT)
                        {
                            GetHistoryOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput>(methodid, timestampGE, timestampLT);
                            return result;
                        }
                    };
                    class GetId
                    {
                    private:
                        const std::string methodName_ = "GetId";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 16;
                    public:
                        GetId(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::GetIdOutput operator()()
                        {
                            GetIdOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetIdOutput>(methodid);
                            return result;
                        }
                    };
                    class GetSwClusterChangeInfo
                    {
                    private:
                        const std::string methodName_ = "GetSwClusterChangeInfo";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 15;

                    public:
                        GetSwClusterChangeInfo(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput operator()()
                        {
                            GetSwClusterChangeInfoOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput>(methodid);
                            return result;
                        }
                    };
                    class GetSwClusterDescription
                    {
                    private:
                        const std::string methodName_ = "GetSwClusterDescription";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 14;
                    public:
                        GetSwClusterDescription(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput operator()()
                        {
                            GetSwClusterDescriptionOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput>(methodid);
                            return result;
                        }
                    };
                    class GetSwClusterInfo
                    {
                    private:
                        const std::string methodName_ = "GetSwClusterInfo";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 13;
                    public:
                        GetSwClusterInfo(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput operator()()
                        {
                            GetSwClusterInfoOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput>(methodid);
                            return result;
                        }
                    };
                    class GetSwPackages
                    {
                    private:
                        const std::string methodName_ = "GetSwPackages";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 12;
                    public:
                        GetSwPackages(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput operator()()
                        {
                            GetSwPackagesOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput>(methodid);
                            return result;
                        }
                    };
                    class GetSwProcessProgress
                    {
                    private:
                        const std::string methodName_ = "GetSwProcessProgress";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 11;
                    public:
                        GetSwProcessProgress(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                        {
                            GetSwProcessProgressOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput>(methodid, id);
                            return result;
                        }
                    };
                    class ProcessSwPackage
                    {
                    private:
                        const std::string methodName_ = "ProcessSwPackage";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid = 10;
                    public:
                        ProcessSwPackage(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                        {
                            ProcessSwPackageOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput>(methodid, id);
                            return result;
                        }
                    };
                    class RevertProcessedSwPackages
                    {
                    private:
                        const std::string methodName_ = "RevertProcessedSwPackages";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid =23;
                    public:
                        RevertProcessedSwPackages(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput operator()()
                        {
                            RevertProcessedSwPackagesOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput>(methodid);
                            return result;
                        }
                    };
                    class Rollback
                    {
                    private:
                        const std::string methodName_ = "Rollback";
                        ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                        const int methodid =22;
                    public:
                        Rollback(ara::com::proxy_skeleton::proxy::ServiceProxy* service_proxy)
                        {
                            this->service_proxy = service_proxy;
                        }

                        const std::string getMethodName();

                        ara::ucm::pkgmgr::PackageManagement::RollbackOutput operator()()
                        {
                            RollbackOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::RollbackOutput>(methodid);
                            return result;
                        }
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
                            TransferDataOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>(methodid, id, blockCounter,data[index]...);
                            return result;
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
                            TransferExitOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput>(methodid, id);
                            return result;
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
                            TransferStartOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>(methodid, size);
                            return result;
                        }

                    };
                }

            }
        }
    }
}

#endif