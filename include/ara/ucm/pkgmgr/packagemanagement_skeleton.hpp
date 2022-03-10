/**
 * @file PackageManagement_skeleton.h
 * @author Sarah Mohamed
 * @brief Skeleton(service provider) file for ucm::pkgmgr
 * @version 0.1
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_UCM_PKGMGR_PackageManagement_SKELETON_H_
#define ARA_UCM_PKGMGR_PackageManagement_SKELETON_H_

#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/ucm/pkgmgr/ucm_types.hpp"
#include <future>
#include "ara/ucm/pkgmgr/packagemanagement_common.hpp"

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace skeleton
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
                 * @brief implementation of PackageManagementSkeleton interface
                 *
                 * @note . Service implementation class is derived from the (service) skeleton.
                 *       . ref: 6.3 Skeleton Class in exp_aracomAPI
                 *
                 * @todo inherit from ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                 */
                class PackageManagementSkeleton
                {
                public:
                    /**
                     * @brief Construct a new Package Management Skeleton object
                     *        Ctor taking instance identifier as parameter and having default
                     *        request processing mode kEvent.
                     *
                     * @param instance
                     * @param mode
                     * @todo implement arguments types
                     *
                     */
                    PackageManagementSkeleton(
                        // ara::com::InstanceIdentifier instance,
                        // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent

                    )
                    {
                    }
                    /**
                     * @todo: - Events
                     *        - Fields
                     *        - Methods
                     */
                    std::future<::ara::ucm::PackageManagerStatusType> CurrentStatus_Get()
                    {
                        std::future<::ara::ucm::PackageManagerStatusType> f;
                        return f;
                    }

                    std::future<ara::ucm::pkgmgr::PackageManagement::ActivateOutput> Activate();
                    std::future<ara::ucm::pkgmgr::PackageManagement::CancelOutput> Cancel(TransferIdType id);
                    std::future<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput> DeleteTransfer(TransferIdType id);
                    std::future<ara::ucm::pkgmgr::PackageManagement::FinishOutput> Finish();
                    void GetHistory(uint64_t timestampGE, uint64_t timestampLT, GetHistoryVectorType &history);
                    void GetId(UCMIdentifierType &id);
                    void GetSwClusterChangeInfo(SwClusterInfoVectorType &SwInfo);
                    void GetSwClusterDescription(SwDescVectorType &SwCluster);
                    void GetSwClusterInfo(SwClusterInfoVectorType &SwInfo);
                    void GetSwPackages(SwPackageInfoVectorType &Packages);
                    std::future<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput> GetSwProcessProgress(TransferIdType id, uint8_t &progress);
                    std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> ProcessSwPackage(TransferIdType id);
                    std::future<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput> RevertProcessedSwPackages();
                    std::future<ara::ucm::pkgmgr::PackageManagement::RollbackOutput> Rollback();
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> TransferData(TransferIdType id, ByteVectorType data, uint64_t size);
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> TransferExit(TransferIdType id);
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> TransferStart(uint64_t size, TransferIdType &id, uint32_t &BlockSize);

                    void DispatchMethodCall()
                    {
                    }
                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PackageManagement_SKELETON_H_ */
