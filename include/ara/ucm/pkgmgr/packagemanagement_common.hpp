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

// using namespace ara::ucm::pkgmgr::PackageManagement;

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            /**
             * @brief class Activate
             * 
             */
            class Activate
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "Activate";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 21;
            
            public:
            /**
             * @brief Construct a new Activate object
             * 
             * @param service_proxy 
             */
                Activate(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();

                /**
                 * @brief PackageManagement ActivateOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::ActivateOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::ActivateOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::ActivateOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::ActivateOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class cancel
             * 
             */
            class Cancel
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "Cancel";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 20;

            public:
            /**
             * @brief Construct a new Cancel object
             * 
             * @param service_proxy 
             */
                Cancel(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement CancelOutput operator
                 * 
                 * @param id 
                 * @return ara::ucm::pkgmgr::PackageManagement::CancelOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::CancelOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::CancelOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::CancelOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class DeleteTransfer
             * 
             */
            class DeleteTransfer
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "DeleteTransfer";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 19;

            public:
            /**
             * @brief Construct a new Delete Transfer object
             * 
             * @param service_proxy 
             */
                DeleteTransfer(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement DeleteTransferOutput operator
                 * 
                 * @param id 
                 * @return ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput 
                 */

                ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class Finish
             * 
             */
            class Finish
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "Finish";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 18;

            public:
            /**
             * @brief Construct a new Finish object
             * 
             * @param service_proxy 
             */
                Finish(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement FinishOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::FinishOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::FinishOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::FinishOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::FinishOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetHistory
             * 
             */
            class GetHistory
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "GetHistory";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 17;

            public:
            /**
             * @brief Get the History object
             * 
             * @param service_proxy 
             */
                GetHistory(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement GetHistoryOutput operator
                 * 
                 * @param timestampGE 
                 * @param timestampLT 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput operator()(uint64_t timestampGE, uint64_t timestampLT)
                {
                    ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput>(methodid, timestampGE, timestampLT);
                    return result;
                }
            };
            /**
             * @brief class GetId
             * 
             */
            class GetId
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "GetId";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 16;

            public:
            /**
             * @brief Get the Id object
             * 
             * @param service_proxy 
             */
                GetId(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                
                const std::string getMethodName();
                /**
                 * @brief PackageManagement GetIdOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetIdOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetIdOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::GetIdOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetIdOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetSwClusterChangeInfo
             * 
             */
            class GetSwClusterChangeInfo
            {
            private:
                /**
                 * @brief private variable
                 * 
                 */
                const std::string methodName_ = "GetSwClusterChangeInfo";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 15;

            public:
                /**
                 * @brief Get the Sw Cluster Change Info object
                 * 
                 * @param service_proxy 
                 */
                GetSwClusterChangeInfo(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement GetSwClusterChangeInfoOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetSwClusterDescription
             * 
             */
            class GetSwClusterDescription
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "GetSwClusterDescription";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 14;

            public:
            /**
             * @brief Get the Sw Cluster Description object
             * 
             * @param service_proxy 
             */
                GetSwClusterDescription(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief GetSwClusterDescriptionOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetSwClusterInfo
             * 
             */
            class GetSwClusterInfo
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "GetSwClusterInfo";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 13;

            public:
            /**
             * @brief Get the Sw Cluster Info object
             * 
             * @param service_proxy 
             */
                GetSwClusterInfo(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement GetSwClusterInfoOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput operator()()
                {
                   ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetSwPackages
             * 
             */
            class GetSwPackages
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "GetSwPackages";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 12;

            public:
            /**
             * @brief Get the Sw Packages object
             * 
             * @param service_proxy 
             */
                GetSwPackages(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();

                ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetSwProcessProgress
             * 
             */
            class GetSwProcessProgress
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "GetSwProcessProgress";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 11;

            public:
            /**
             * @brief Get the Sw Process Progress object
             * 
             * @param service_proxy 
             */
                GetSwProcessProgress(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief GetSwProcessProgressOutput operator
                 * 
                 * @param id 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class ProcessSwPackage
             * 
             */
            class ProcessSwPackage
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "ProcessSwPackage";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 10;

            public:
            /**
             * @brief Construct a new Process Sw Package object
             * 
             * @param service_proxy 
             */
                ProcessSwPackage(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                 /**
                  * @brief PackageManagement ProcessSwPackageOutput operator
                  * 
                  * @param id 
                  * @return ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput 
                  */
                ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class RevertProcessedSwPackages
             * 
             */
            class RevertProcessedSwPackages
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "RevertProcessedSwPackages";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 23;

            public:
            /**
             * @brief Construct a new Revert Processed Sw Packages object
             * 
             * @param service_proxy 
             */
                RevertProcessedSwPackages(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief RevertProcessedSwPackagesOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class Rollback
             * 
             */
            class Rollback
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "Rollback";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 22;

            public:
            /**
             * @brief Construct a new Rollback object
             * 
             * @param service_proxy 
             */
                Rollback(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement RollbackOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::RollbackOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::RollbackOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::RollbackOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::RollbackOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class TransferData
             * 
             */
            class TransferData
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "TransferData";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 8;

            public:
            /**
             * @brief Construct a new Transfer Data object
             * 
             * @param service_proxy 
             */
                TransferData(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement TransferDataOutput operator
                 * 
                 * @param id 
                 * @param data 
                 * @param blockCounter 
                 * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> 
                 */
                std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter)
                {
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>result = std::async([&,id, blockCounter, data](){
                    ara::com::Serializer ser;
                    // ser.serialize(methodid);
                    ser.serialize(id);
                    ser.serialize(blockCounter);
                    std::vector<uint8_t> msgser = ser.Payload();
                    msgser.insert(msgser.end(), data.begin(), data.end());

                    return service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>(methodid, msgser);
                    
                    });
                    return result;
                
                    // return send(id, data, blockCounter, std::make_index_sequence<N>{});
                    
                }
                // template <std::size_t... index>
                // std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> send(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter, std::index_sequence<index...>)
                // {
                //     // std::future<boost::variant2::variant<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput, ara::ucm::pkgmgr::PackageManagement::UCMErrorDomain>> result = service_proxy->SendRequest<std::future<boost::variant2::variant<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput, ara::ucm::pkgmgr::PackageManagement::UCMErrorDomain>>>(methodid, id, blockCounter, data[index]...);
                //     // return result;

                //     std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>result = std::async([&,id, blockCounter, data](){
                //     for(int i = 0 ; i < 64; i++)
                //     {
                //         printf("%x", data[i]);
                //     }
                //     std::cout << std::endl;
                //     return service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>(methodid, id, blockCounter, data[index]...);
                    
                //     });
                //     return result;
                // }
            };
            /**
             * @brief class TransferExit
             * 
             */
            class TransferExit
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "TransferExit";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 9;

            public:
            /**
             * @brief Construct a new Transfer Exit object
             * 
             * @param service_proxy 
             */
                TransferExit(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement TransferExitOutput operator
                 * 
                 * @param id 
                 * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> 
                 */
                std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    // ara::ucm::pkgmgr::PackageManagement::TransferExitOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput>(methodid, id);
                    // return result;
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> result = std::async([&, id](){
                    return service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput>(methodid, id);
                    
                    });
                    return result;
                }
            };
            /**
             * @brief class TransferStart
             * 
             */
            class TransferStart
            {
            private:
            /**
             * @brief private variable
             * 
             */
                const std::string methodName_ = "TransferStart";
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                const int methodid = 7;

            public:
            /**
             * @brief Construct a new Transfer Start object
             * 
             * @param service_proxy 
             */
                TransferStart(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                const std::string getMethodName();
                /**
                 * @brief PackageManagement::TransferStartOutput operator
                 * 
                 * @param size 
                 * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> 
                 */

                std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> operator()(uint64_t size)
                {
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> result = std::async([&, size](){
                    return service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>(methodid, size);
                    
                    });
                    return result;
                    
                }
            };
        }

    }
}

#endif