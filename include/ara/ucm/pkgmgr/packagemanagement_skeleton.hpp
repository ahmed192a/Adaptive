/**
 * @file PackageManagement_skeleton.h
 * @author Flashing Adapter Graduation Project Team
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
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/ucm/pkgmgr/ucm_types.hpp"
#include "ara/ucm/pkgmgr/ucm_return_types.hpp"
#include "ara/ucm/pkgmgr/ucm_error.hpp"
#include "ara/ucm/pkgmgr/packet.hpp"
#include <future>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
// #include <boost/uuid/uuid_generators.hpp>
// #include <boost/uuid/uuid_io.hpp>
// #include <boost/lexical_cast.hpp>
// #include <boost/variant2/variant.hpp>
// #include <bits/stdc++.h>


using namespace boost::uuids;

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace skeleton
            {

                namespace fields
                {
                    /**
                     * @brief The current status of UCM PackageManagement.
                     * 
                     * Template order <tyep , getter, setter, Notifier>
                     */
                    using CurrentStatus = ara::com::proxy_skeleton::skeleton::FieldType<::ara::ucm::pkgmgr::PackageManagement::PackageManagerStatusType, true, false, true>::type;
                }

                /**
                 * @brief implementation of PackageManagementSkeleton interface
                 *
                 * @note . Service implementation class is derived from the (service) skeleton.
                 *
                 */
                class PackageManagementSkeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    struct TransferInfo
                    {
                        uint8_t TransferExitFlag; /* After calling TransferExit, can't call TransferData again */
                        uint32_t BlockSize;       /* Block size generated from transfer start */ 
                        PackageManagement::TransferIdType id; /* unique ID of Swpackage generated from transfer start */
                        uint64_t size;                      
                        uint64_t localBlockCounter = 0;
                        uint64_t lastBlockCounter = 0;
                    } TransferInfoData;

                    // buffer to stor Sw package 
                    std::vector<uint8_t> buffer;  
                    // Service ID of UCM Package management service  
                    ara::com::proxy_skeleton::ServiceId UCM_Service_id ;
                    // current software process progress
                    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput currentSwProcessProgress ={0};

                public:
                    /**
                     * @brief Construct a new Package Management Skeleton object
                     *        Ctor taking instance identifier as parameter and having default
                     *        request processing mode kEvent.
                     *
                     * @param instance
                     * @param mode
                     *
                     */
                    PackageManagementSkeleton(
                        ara::com::InstanceIdentifier instance,
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle) : UCM_Service_id(45),
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton(UCM_Service_id, instance, skeleton_handle),
                        CurrentStatus(this, "CurrentStatus", 0)
                    {
                    }

                    // ara::ucm::pkgmgr::PackageManagement::PackageManagerStatusType CurrentStatus_Get()
                    // {
                    // }

 // *********** Methods
                    /**
                     * @brief Activate the software package
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::ActivateOutput 
                     */
                    std::future<ara::ucm::pkgmgr::PackageManagement::ActivateOutput> Activate();
                    /**
                     * @brief Cancel
                     * 
                     * @param id 
                     * @return ara::ucm::pkgmgr::PackageManagement::CancelOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::CancelOutput Cancel(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    /**
                     * @brief Delete Transfer
                     * 
                     * @param id 
                     * @return ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput DeleteTransfer(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    /**
                     * @brief Finsih
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::FinishOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::FinishOutput Finish();
                    /**
                     * @brief Get the History 
                     * 
                     * @param timestampGE 
                     * @param timestampLT 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput GetHistory(uint64_t timestampGE, uint64_t timestampLT);
                    /**
                     * @brief Get the Id 
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetIdOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetIdOutput GetId();
                    /**
                     * @brief Get the Sw Cluster Change Info 
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput GetSwClusterChangeInfo();
                    /**
                     * @brief Get the Sw Cluster Description 
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput GetSwClusterDescription();
                    /**
                     * @brief Get the Sw Cluster Info 
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput GetSwClusterInfo();
                    /**
                     * @brief Get the Sw Packages 
                     * 
                     * @param Packages 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput GetSwPackages(ara::ucm::pkgmgr::PackageManagement::SwPackageInfoVectorType &Packages);
                    /**
                     * @brief Get the Sw Process Progress 
                     * 
                     * @param id 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput 
                     */
                    std::future<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput> GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    /**
                     * @brief Get the Sw Process Progress 
                     * 
                     * @param id 
                     * @param progress 
                     * @return ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, uint8_t &progress);
                    /**
                     * @brief start processing the Software package
                     * 
                     * @param id 
                     * @return std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> 
                     */
                    std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    /**
                     * @brief Revert Processed Software Packages to previous version
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput RevertProcessedSwPackages();
                    /**
                     * @brief Rollback
                     * 
                     * @return ara::ucm::pkgmgr::PackageManagement::RollbackOutput 
                     */
                    ara::ucm::pkgmgr::PackageManagement::RollbackOutput Rollback();
                    /**
                     * @brief Trasfer the data of SwPAckage from Client to server
                     * 
                     * @param id 
                     * @param data 
                     * @param blockCounter 
                     * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> 
                     */
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> TransferData(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter);
                    /**
                     * @brief Request Trasfer Exit
                     * 
                     * @param id 
                     * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> 
                     */
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> TransferExit(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    /**
                     * @brief Request Trasfer start
                     * 
                     * @param size 
                     * @return std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> 
                     */
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> TransferStart(uint64_t size);
                    
                    // *********** Fields
                    fields::CurrentStatus CurrentStatus; // Field of the current status of package management

// *********** Dispatching Methods
                    /**
                     * @brief Dispatch the requested methods from fields of package management server
                     * 
                     * @param message 
                     * @param cserver 
                     */
                    void field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver);

                    /**
                     * @brief Dispatch the requested methods from package management server
                     * 
                     * @param message 
                     * @param cserver 
                     */
                    void method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver);

                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PackageManagement_SKELETON_H_ */
