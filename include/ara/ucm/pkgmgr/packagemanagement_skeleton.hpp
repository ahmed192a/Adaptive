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
                    ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput GetHistory(uint64_t timestampGE, uint64_t timestampLT);
                    ara::ucm::pkgmgr::PackageManagement::GetIdOutput GetId();
                    ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput GetSwClusterChangeInfo();
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

                    void method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;

                        int methodID = message.MessageId().method_id;

                        cout << "\t[SERVER] Dispatch " << methodID << endl;

                        switch (methodID)
                        {
                        case 7:
                            HandleCall(*this, &PackageManagementSkeleton::TransferStart, message, cserver);

                            break;
                        case 8:
                        {
                            std::vector<uint8_t> msg = message.GetPayload();
                            ara::ucm::pkgmgr::PackageManagement::ByteVectorType data;
                            uint64_t blockCounter = dser.deserialize<uint64_t>(msg, 16);
                            ara::ucm::pkgmgr::PackageManagement::TransferIdType id = dser.deserialize<ara::ucm::pkgmgr::PackageManagement::TransferIdType>(msg, 0);
                            std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> transfer_data_output;
                            ara::ucm::pkgmgr::PackageManagement::TransferDataOutput rval;

                            // //HandleCall(*this, &PackageManagementSkeleton::TransferData, msg, cserver);

                            data.clear();
                            data.insert(data.begin(), msg.begin() + 24, msg.end());

                            // cout << "msgsize" << msg.size() << endl;
                            transfer_data_output = TransferData(id, data, blockCounter);
                            rval = transfer_data_output.get();
                            // create message and send it
                            ara::com::SOMEIP_MESSAGE::Message response_m(
                                ara::com::SOMEIP_MESSAGE::Message_ID{(uint16_t)this->serviceid.GetInstanceId(), (uint16_t)(message.MessageId().method_id & 0x7fff)},
                                ara::com::SOMEIP_MESSAGE::Request_ID{5, 6},
                                2, // protocol version
                                7, // Interface Version
                                ara::com::SOMEIP_MESSAGE::MessageType::RESPONSE);

                            // create serialize object
                            ara::com::Serializer s1;
                            // serialize the result
                            s1.serialize(rval);
                            std::vector<uint8_t> _payload = s1.Payload();
                            response_m.SetPayload(_payload);
                            _payload.clear();
                            _payload = response_m.Serializer();


                            uint32_t msg_size = _payload.size();
                            // send message
                            cserver.Send(&msg_size, sizeof(msg_size));
                            cserver.Send(_payload.data(), msg_size);
                            cserver.CloseSocket();
                        }

                        break;
                        case 9:
                            HandleCall(*this, &PackageManagementSkeleton::TransferExit, message, cserver);
                            break;
                        case 10:
                            HandleCall(*this, &PackageManagementSkeleton::ProcessSwPackage, message, cserver);
                            break;
                        default:
                            // cserver.Send(&result, sizeof(int));
                            // cserver.CloseSocket();
                            break;
                        }
                    }
                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PackageManagement_SKELETON_H_ */
