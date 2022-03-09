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

#include "ara/ucm/pkgmgr/inc.hpp"
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
                     * @todo update typedef:
                     *       field: CurrentStatus of type: PackageManagementStatusType
                     * @note int de ay haga mo2ktn
                     * 
                     */
                    using CurrentStatus = ara::com::proxy_skeleton::skeleton::FieldType<::ara::ucm::PackageManagerStatusType, true, true, false>::type;
                }
                /**
                 * @brief implementation of PackageManagementProxy interface
                 * 
                 * @note . It is an instance of a C++ class local to the application/client, which uses the service.
                 *       . ref: 6.2 Proxy Class in exp_aracomAPI
                 * 
                 * @todo inherit from ara::com::proxy_skeleton::proxy::ServiceProxy
                 */
                class PackageManagementProxy : public ara::com::proxy_skeleton::proxy::ServiceProxy
                {
                public:
                    /**
                         * @todo: - ctor
                         *        - Events
                         *        - Fields
                         *        - Methods
                         *        - findservice function
                         */
                    PackageManagementProxy();

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

                    
                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_ */
