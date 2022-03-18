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
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/ucm/pkgmgr/ucm_types.hpp"
#include "ucm_return_types.hpp"
#include "ucm_error.hpp"
#include <future>

#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/variant2/variant.hpp>
#include <bits/stdc++.h>
using namespace boost::uuids;

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
                    using CurrentStatus = ara::com::proxy_skeleton::skeleton::FieldType<::ara::ucm::pkgmgr::PackageManagement::PackageManagerStatusType, true, true, false>::type;
                }
                /**
                 * @brief implementation of PackageManagementSkeleton interface
                 *
                 * @note . Service implementation class is derived from the (service) skeleton.
                 *       . ref: 6.3 Skeleton Class in exp_aracomAPI
                 *
                 * @todo inherit from ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                 */
                class PackageManagementSkeleton : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                private:
                    struct TransferInfo
                    {
                        uint8_t TransferExitFlag; /* After calling TransferExit, can't call TransferData again */
                        uint32_t BlockSize;       // 10, localCounter: 0 -> 9 (localCounter + 1) * BlockSize == size
                        ara::ucm::pkgmgr::PackageManagement::TransferIdType id;
                        uint64_t size; // 100 bytes
                        uint64_t localBlockCounter = 0;
                    } TransferInfoData;

                    std::vector<uint8_t> buffer;
                    ara::com::InstanceIdentifier serviceid;

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
                        // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
                        ara::com::InstanceIdentifier instance,
                        ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle) : serviceid(45),
                            ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle)

                    {
                    }
                    /**
                     * @todo: - Events
                     *        - Fields
                     *        - Methods
                     */
                    ara::ucm::pkgmgr::PackageManagement::PackageManagerStatusType CurrentStatus_Get()
                    {
                    }

                    ara::ucm::pkgmgr::PackageManagement::ActivateOutput Activate();
                    ara::ucm::pkgmgr::PackageManagement::CancelOutput Cancel(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput DeleteTransfer(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    ara::ucm::pkgmgr::PackageManagement::FinishOutput Finish();
                    ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput  GetHistory(uint64_t timestampGE, uint64_t timestampLT);
                    ara::ucm::pkgmgr::PackageManagement::GetIdOutput GetId();
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput  GetSwClusterChangeInfo();
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput GetSwClusterDescription();
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput GetSwClusterInfo();
                    ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput GetSwPackages(ara::ucm::pkgmgr::PackageManagement::SwPackageInfoVectorType &Packages);
                    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);

                    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, uint8_t &progress);
                    std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput RevertProcessedSwPackages();
                    ara::ucm::pkgmgr::PackageManagement::RollbackOutput Rollback();
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> TransferData(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter);
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> TransferExit(ara::ucm::pkgmgr::PackageManagement::TransferIdType id);
                    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> TransferStart(uint64_t size);

                    void method_dispatch(std::vector<uint8_t> &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;
                        int methodID = dser.deserialize<int>(message, 0);
                        int result = -1;
                        cout << "\t[SERVER] Dispatch " << methodID << endl;
                        std::vector<uint8_t> msg;
                        msg.insert(msg.begin(), message.begin() + sizeof(int), message.end());
                        ara::ucm::pkgmgr::PackageManagement::ByteVectorType data;
                        uint64_t blockCounter;
                        ara::ucm::pkgmgr::PackageManagement::TransferIdType id;
                        std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> transfer_data_output;
                        int i;
                        ara::ucm::pkgmgr::PackageManagement::TransferDataOutput rval;
                        switch (methodID)
                        {
                        case 7:
                        cout << dser.deserialize<uint64_t>(msg, 0) << std::endl;
                        // cout << "msgsize" << msg.size() << endl;
                            HandleCall(*this, &PackageManagementSkeleton::TransferStart, msg, cserver);
                            break;
                        case 8:
                            // HandleCall(*this, &PackageManagementSkeleton::TransferData, msg, cserver);
                            id = dser.deserialize<ara::ucm::pkgmgr::PackageManagement::TransferIdType>(msg, 0);
                            blockCounter = dser.deserialize<uint64_t>(msg, 16);
                            data.clear();
                            data.insert(data.begin(), msg.begin() + 24, msg.end());

                            // cout << "msgsize" << msg.size() << endl;
                            transfer_data_output = TransferData(id, data, blockCounter);
                            rval = transfer_data_output.get();
                            cserver.Send(&rval, sizeof(rval));
                            cserver.CloseSocket();
                            break;
                        case 9:
                           HandleCall(*this, &PackageManagementSkeleton::TransferExit, msg, cserver);
                            break;
                        case 10:
                            HandleCall(*this, &PackageManagementSkeleton::ProcessSwPackage, msg, cserver);
                            break;
                        default:
                            cserver.Send(&result, sizeof(int));
                            cserver.CloseSocket();
                            break;
                        }
                    }
                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PackageManagement_SKELETON_H_ */
