/**
 * @file package_management.cpp
 * @brief Definition of Provided Port(PackageManagement) methods
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include "ara/ucm/pkgmgr/packagemanagement_common.hpp"
#include "ara/ucm/pkgmgr/ucm_error.hpp"

using namespace ara::ucm::pkgmgr::skeleton;
using namespace ara::ucm;

std::future<ara::ucm::pkgmgr::PackageManagement::ActivateOutput> PackageManagementSkeleton::Activate()
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::ActivateOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::ActivateOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::ActivateOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::CancelOutput> PackageManagementSkeleton::Cancel(TransferIdType id)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::CancelOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::CancelOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::CancelOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput> PackageManagementSkeleton::DeleteTransfer(TransferIdType id)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::FinishOutput> PackageManagementSkeleton::Finish()
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::FinishOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::FinishOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::FinishOutput> future = promise->get_future();
    return future;
}

void PackageManagementSkeleton::GetHistory(uint64_t timestampGE, uint64_t timestampLT, GetHistoryVectorType &history)
{

}

void PackageManagementSkeleton::GetId(UCMIdentifierType &id)
{

}

void PackageManagementSkeleton::GetSwClusterChangeInfo(SwClusterInfoVectorType &SwInfo)
{

}

void PackageManagementSkeleton::GetSwClusterDescription(SwDescVectorType &SwCluster)
{

}

void PackageManagementSkeleton::GetSwClusterInfo(SwClusterInfoVectorType &SwInfo)
{

}

void PackageManagementSkeleton::GetSwPackages(SwPackageInfoVectorType &Packages)
{
  
}

std::future<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput> PackageManagementSkeleton::GetSwProcessProgress(TransferIdType id, uint8_t &progress)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> PackageManagementSkeleton::ProcessSwPackage(TransferIdType id)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> future = promise->get_future();
    return future;

}

std::future<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput> PackageManagementSkeleton::RevertProcessedSwPackages()
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::RollbackOutput> PackageManagementSkeleton::Rollback()
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::RollbackOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::RollbackOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::RollbackOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> PackageManagementSkeleton::TransferData(TransferIdType id, ByteVectorType data, uint64_t size)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> future = promise->get_future();
    return future;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> PackageManagementSkeleton::TransferExit(TransferIdType id)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> future = promise->get_future();
    return future;
}


std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> PackageManagementSkeleton::TransferStart(uint64_t size, TransferIdType &id, uint32_t &BlockSize)
{
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> future = promise->get_future();
    return future;
}

