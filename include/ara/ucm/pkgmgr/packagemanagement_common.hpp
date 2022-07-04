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

#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
#include "ara/ucm/pkgmgr/ucm_return_types.hpp"
#include "ara/ucm/pkgmgr/ucm_types.hpp"
#include <bits/stdc++.h>


namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            /**
             * @brief class Activate Package for the UCM
             *          - This class is used to activate a package
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class Activate
            {
            private:
                /// method name
                const std::string methodName_ = "Activate";          
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;   
                /// method id 
                const int methodid = 21;                             
            
            public:
                /**
                 * @brief Construct a new Activate object
                 * 
                 * @param service_proxy pointer to service proxy object
                 */
                Activate(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }

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
             * @brief class cancel  for the UCM
             *          - This class is used to cancel a package
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class Cancel
            {
            private:
                /// method name
                const std::string methodName_ = "Cancel";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 20;

            public:
                /**
                 * @brief Construct a new Cancel object
                 * 
                 * @param service_proxy  pointer to service proxy object
                 */
                Cancel(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
                /**
                 * @brief PackageManagement CancelOutput operator
                 * 
                 * @param id   id of the package to be cancelled
                 * @return ara::ucm::pkgmgr::PackageManagement::CancelOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::CancelOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::CancelOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::CancelOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class DeleteTransfer for the UCM
             *          - This class is used to delete a transfer
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class DeleteTransfer
            {
            private:
                /// method name
                const std::string methodName_ = "DeleteTransfer";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 19;

            public:
                /**
                 * @brief Construct a new Delete Transfer object
                 * 
                 * @param service_proxy  pointer to service proxy object
                 *
                 */
                DeleteTransfer(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
                /**
                 * @brief PackageManagement DeleteTransferOutput operator
                 * 
                 * @param id    id of the package to be deleted
                 * @return ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput 
                 */

                ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class Finish for the UCM
             *          - This class is used to finish a package
             *          - it's a proxy method that calls the UCM service
             */
            class Finish
            {
            private:
                /// method name
                const std::string methodName_ = "Finish";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 18;

            public:
                /**
                 * @brief Construct a new Finish object
                 * 
                 * @param service_proxy  pointer to service proxy object
                 *
                 */
                Finish(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
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
             * @brief class GetHistory for the UCM
             *          - This class is used to get the history of a package
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class GetHistory
            {
            private:
                /// method name
                const std::string methodName_ = "GetHistory";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 17;

            public:
                /**
                 * @brief Get the History object
                 * 
                 * @param service_proxy  pointer to service proxy object
                 *
                 */
                GetHistory(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
                /**
                 * @brief PackageManagement GetHistoryOutput operator
                 * 
                 * @param timestampGE   timestamp greater or equal to
                 * @param timestampLT   timestamp less than or equal to
                 * @return ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput operator()(uint64_t timestampGE, uint64_t timestampLT)
                {
                    ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput>(methodid, timestampGE, timestampLT);
                    return result;
                }
            };
            /**
             * @brief class GetId   for the UCM
             *         - This class is used to get the id of a package
             *        - it's a proxy method that calls the UCM service
             * 
             */
            class GetId
            {
            private:
                /// method name
                const std::string methodName_ = "GetId";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 16;

            public:
                /**
                 * @brief Get the Id object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 */
                GetId(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
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
             * @brief class GetSwClusterChangeInfo  for the UCM
             *         - This class is used to get the sw cluster change info of a package
             *       - it's a proxy method that calls the UCM service
             * 
             */
            class GetSwClusterChangeInfo
            {
            private:
                /// method name
                const std::string methodName_ = "GetSwClusterChangeInfo";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 15;

            public:
                /**
                 * @brief Get the Sw Cluster Change Info object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                GetSwClusterChangeInfo(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
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
             * @brief class GetSwClusterDescription for the UCM
             *        - This class is used to get the sw cluster description of a package
             *     - it's a proxy method that calls the UCM service
             * 
             */
            class GetSwClusterDescription
            {
            private:
                /// method name
                const std::string methodName_ = "GetSwClusterDescription";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 14;

            public:
                /**
                 * @brief Get the Sw Cluster Description object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 */
                GetSwClusterDescription(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
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
             * @brief class GetSwClusterInfo for the UCM
             *          - This class is used to get the sw cluster info of a package
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class GetSwClusterInfo
            {
            private:
                /// method name
                const std::string methodName_ = "GetSwClusterInfo";
               /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 13;

            public:
                /**
                 * @brief Get the Sw Cluster Info object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                GetSwClusterInfo(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
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
             * @brief class GetSwPackages for the UCM
             *          - This class is used to get the sw packages of a package
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class GetSwPackages
            {
            private:
                /// method name
                const std::string methodName_ = "GetSwPackages";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 12;

            public:
                /**
                 * @brief Get the Sw Packages object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 */
                GetSwPackages(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }

                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
                /**
                 * @brief  PackageManagement GetSwPackagesOutput operator
                 * 
                 * @return ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput operator()()
                {
                    ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput>(methodid);
                    return result;
                }
            };
            /**
             * @brief class GetSwProcessProgress for the UCM
             *         - This class is used to get the sw process progress of a package
             *        - it's a proxy method that calls the UCM service
             * 
             */
            class GetSwProcessProgress
            {
            private:
                /// method name
                const std::string methodName_ = "GetSwProcessProgress";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 11;

            public:
                /**
                 * @brief Get the Sw Process Progress object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                GetSwProcessProgress(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
                /**
                 * @brief GetSwProcessProgressOutput operator
                 * 
                 * @param id  the id of the package to get the progress
                 * @return ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput 
                 */
                ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
                {
                    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput result = service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput>(methodid, id);
                    return result;
                }
            };
            /**
             * @brief class ProcessSwPackage for the UCM
             *          - This class is used to process a sw package
             *          - it's a proxy method that calls the UCM service
             * 
             */
            class ProcessSwPackage
            {
            private:
                /// method name
                const std::string methodName_ = "ProcessSwPackage";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 10;

            public:
                /**
                 * @brief Construct a new Process Sw Package object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                ProcessSwPackage(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
                 /**
                  * @brief PackageManagement ProcessSwPackageOutput operator
                  * 
                  * @param id  the id of the package to process
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
             *         - This class is used to revert a processed sw package
             *        - it's a proxy method that calls the UCM service
             * 
             */
            class RevertProcessedSwPackages
            {
            private:
                /// method name
                const std::string methodName_ = "RevertProcessedSwPackages";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 23;

            public:
                /**
                 * @brief Construct a new Revert Processed Sw Packages object
                 * 
                 * @param service_proxy     pointer to the service proxy
                 */
                RevertProcessedSwPackages(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
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
             * @brief class Rollback Sw Packages
             *        - This class is used to rollback a sw package
             *          - it's a proxy method that calls the UCM service
             *
             */
            class Rollback
            {
            private:
                /// method name
                const std::string methodName_ = "Rollback";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 22;

            public:
                /**
                 * @brief Construct a new Rollback object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                Rollback(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }   

                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
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
             * @brief class TransferData for the UCM
             *        - This class is used to transfer data to the UCM
             *        - it's a proxy method that calls the UCM service
             * 
             */
            class TransferData
            {
            private:
                /// method name
                const std::string methodName_ = "TransferData";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 8;

            public:
                /**
                 * @brief Construct a new Transfer Data object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 */
                TransferData(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
                /**
                 * @brief PackageManagement TransferDataOutput operator
                 * 
                 * @param id            id of the package to transfer data
                 * @param data          data to be transfered
                 * @param blockCounter  block counter of the data
                 * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> 
                 */
                std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> operator()(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter)
                {
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>result = std::async([&,id, blockCounter, data](){
                    ara::com::Serializer ser;       // serializer for the request
                    ser.serialize(id);              // serialize the id
                    ser.serialize(blockCounter);    // serialize the block counter
                    std::vector<uint8_t> msgser = ser.Payload();    // get the serialized data
                    msgser.insert(msgser.end(), data.begin(), data.end());  // append the data to the serialized data
                    // send the request to the service and receive the response
                    return service_proxy->SendRequest<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>(methodid, msgser);   
                    
                    });
                    return result;                    
                }
                
            };
            /**
             * @brief class TransferExit for the UCM
             *       - This class is used to transfer data to the UCM
             *      - it's a proxy method that calls the UCM service
             * 
             */
            class TransferExit
            {
            private:
                /// method name
                const std::string methodName_ = "TransferExit";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 9;

            public:
                /**
                 * @brief Construct a new Transfer Exit object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                TransferExit(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName()
                {
                    return methodName_;
                }
                /**
                 * @brief PackageManagement TransferExitOutput operator
                 * 
                 * @param id          id of the package to transfer data
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
             * @brief class TransferStart for the UCM
             *          - This class is used to transfer data to the UCM
             *          - it's a proxy method that calls the UCM service
             */
            class TransferStart
            {
            private:
                /// method name
                const std::string methodName_ = "TransferStart";
                /// service proxy
                ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy;
                /// method id
                const int methodid = 7;

            public:
                /**
                 * @brief Construct a new Transfer Start object
                 * 
                 * @param service_proxy  pointer to the service proxy
                 *
                 */
                TransferStart(ara::com::proxy_skeleton::proxy::ServiceProxy *service_proxy)
                {
                    this->service_proxy = service_proxy;
                }
                /**
                 * @brief Get the Method Name object
                 * 
                 * @return const std::string 
                 */
                const std::string getMethodName(){
                    return methodName_;
                }
                /**
                 * @brief PackageManagement::TransferStartOutput operator
                 * 
                 * @param size      size of the data to be transferred
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