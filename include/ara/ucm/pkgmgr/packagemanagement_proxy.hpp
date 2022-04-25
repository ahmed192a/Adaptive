/**
 * @file packagemanagement_proxy.h
 * @author Sarah Mohamed
 * @brief Proxy(service requester) file for ucm::pkgmgr service interface
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_

#include "packagemanagement_common.hpp"
#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace proxy
            {
                namespace events
                {

                }
                namespace fields
                {
                    /**
                     * @brief The current status of UCM.
                     * 
                     * 
                     */
                    using CurrentStatus = ara::com::proxy_skeleton::proxy::FieldType<ara::ucm::pkgmgr::PackageManagement::PackageManagerStatusType, true, true, true>::type;
                }
                namespace methods
                {
                    using Activate = ara::ucm::pkgmgr::Activate;
                    using Cancel = ara::ucm::pkgmgr::Cancel;
                    using DeleteTransfer = ara::ucm::pkgmgr::DeleteTransfer;
                    using Finish = ara::ucm::pkgmgr::Finish;
                    using GetHistory = ara::ucm::pkgmgr::GetHistory;
                    using GetId = ara::ucm::pkgmgr::GetId;
                    using GetSwClusterChangeInfo = ara::ucm::pkgmgr::GetSwClusterChangeInfo;
                    using GetSwClusterDescription = ara::ucm::pkgmgr::GetSwClusterDescription;
                    using GetSwClusterInfo = ara::ucm::pkgmgr::GetSwClusterInfo;
                    using GetSwPackages = ara::ucm::pkgmgr::GetSwPackages;
                    using GetSwProcessProgress = ara::ucm::pkgmgr::GetSwProcessProgress;
                    using ProcessSwPackage = ara::ucm::pkgmgr::ProcessSwPackage;
                    using RevertProcessedSwPackages = ara::ucm::pkgmgr::RevertProcessedSwPackages;
                    using Rollback = ara::ucm::pkgmgr::Rollback;
                    using TransferData= ara::ucm::pkgmgr::TransferData;
                    using TransferExit = ara::ucm::pkgmgr::TransferExit;
                    using TransferStart = ara::ucm::pkgmgr::TransferStart;
 
                } // namespace methods
                 
                /**
                 * @brief implementation of PackageManagementProxy interface
                 * 
                 * @note . It is an instance of a C++ class local to the application/client, which uses the service.
                 *       . ref: 6.2 Proxy Class in exp_aracomAPI
                 * 
                 */
                class PackageManagementProxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    PackageManagementProxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
                    : ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle),
                     TransferStart(this),
                     TransferData(this),
                     TransferExit(this),
                     Rollback(this),
                     RevertProcessedSwPackages(this),
                     ProcessSwPackage(this),
                     GetSwProcessProgress(this),
                     GetSwPackages(this),
                     GetSwClusterInfo(this),
                     GetSwClusterDescription(this),
                     GetSwClusterChangeInfo(this),
                     GetId(this),
                     GetHistory(this),
                     Finish(this),
                     DeleteTransfer(this),
                     Cancel(this),
                     Activate(this),
                     CurrentStatus(this,"CurrentStatus", 0)
                    {

                    }

                    methods::Activate Activate;
                    methods::Cancel Cancel;
                    methods::DeleteTransfer DeleteTransfer;
                    methods::Finish Finish;
                    methods::GetHistory GetHistory;
                    methods::GetId GetId;
                    methods::GetSwClusterChangeInfo GetSwClusterChangeInfo;
                    methods::GetSwClusterDescription GetSwClusterDescription;
                    methods::GetSwClusterInfo GetSwClusterInfo;
                    methods::GetSwPackages GetSwPackages;
                    methods::GetSwProcessProgress GetSwProcessProgress;
                    methods::ProcessSwPackage ProcessSwPackage;
                    methods::RevertProcessedSwPackages RevertProcessedSwPackages;
                    methods::Rollback Rollback;
                    methods::TransferData TransferData;
                    methods::TransferExit TransferExit;
                    methods::TransferStart TransferStart;
                    fields::CurrentStatus CurrentStatus;
                    
                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_ */
