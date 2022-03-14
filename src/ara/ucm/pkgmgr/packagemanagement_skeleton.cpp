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

void SaveBlock(const char *filename, std::vector<uint8_t> &data_block)
{
    std::ofstream outfile(filename, std::ios::out | std::ofstream::app);
    outfile.write((const char *)&data_block[0], data_block.size());
    outfile.close();
}

ara::ucm::pkgmgr::PackageManagement::ActivateOutput PackageManagementSkeleton::Activate()
{
 
}

ara::ucm::pkgmgr::PackageManagement::CancelOutput PackageManagementSkeleton::Cancel(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{

}

ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput PackageManagementSkeleton::DeleteTransfer(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
 
}

ara::ucm::pkgmgr::PackageManagement::FinishOutput PackageManagementSkeleton::Finish()
{

}

void PackageManagementSkeleton::GetHistory(uint64_t timestampGE, uint64_t timestampLT, ara::ucm::pkgmgr::PackageManagement::GetHistoryVectorType &history)
{

}

void PackageManagementSkeleton::GetId(ara::ucm::pkgmgr::PackageManagement::UCMIdentifierType &id)
{

}

void PackageManagementSkeleton::GetSwClusterChangeInfo(ara::ucm::pkgmgr::PackageManagement::SwClusterInfoVectorType &SwInfo)
{

}

void PackageManagementSkeleton::GetSwClusterDescription(ara::ucm::pkgmgr::PackageManagement::SwDescVectorType &SwCluster)
{

}

void PackageManagementSkeleton::GetSwClusterInfo(ara::ucm::pkgmgr::PackageManagement::SwClusterInfoVectorType &SwInfo)
{

}

void PackageManagementSkeleton::GetSwPackages(ara::ucm::pkgmgr::PackageManagement::SwPackageInfoVectorType &Packages)
{
  
}

ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput PackageManagementSkeleton::GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, uint8_t &progress)
{
   
}

ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput PackageManagementSkeleton::ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{


}

ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput PackageManagementSkeleton::RevertProcessedSwPackages()
{
   
}
ara::ucm::pkgmgr::PackageManagement::RollbackOutput PackageManagementSkeleton::Rollback()
{
    
}

ara::ucm::pkgmgr::PackageManagement::TransferDataOutput PackageManagementSkeleton::TransferData(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter)
{
    ara::ucm::pkgmgr::PackageManagement::TransferDataOutput result;
    if (TransferInfoData.id == id)
    {
        
        if (blockCounter == TransferInfoData.localBlockCounter)
        {
            std::cout << "data size: " << data.size() << std::endl;
            /* Check if the received block size is equal the block size returned by TransferStart for the same TransferId */
            if (data.size() == TransferInfoData.BlockSize)
            {
                std::cout << "xxxx" << std::endl;
                // uint32_t i = TransferInfoData.localBlockCounter * TransferInfoData.BlockSize;
                // copy(data.begin(), data.end(), std::back_inserter(PackageManagementSkeleton::buffer));
                for(int i = 0; i < TransferInfoData.BlockSize; i++)
                {
                    buffer.push_back(data[i]);
                }
                
                std::cout << buffer.size() << std::endl;
                // this if reaches last block
                // if ((TransferInfoData.localBlockCounter + 1) * TransferInfoData.BlockSize == TransferInfoData.size)
                // {

                // }
                
                //SaveBlock("/home/basmala/Desktop/Gradution_project/test1/myfile3.zip" , data);
            }
            else 
            {
                // ApplicationError IncorrectBlockSize -> Too big block size received by UCM
                // In case the received block size with TransferData 
                // exceeds the block size returned by TransferStart for the same TransferId
            }
        }
        else 
        {
            // ApplicationError BlockInconsistent
            // ApplicationError IncorrectBlock
        }
        TransferInfoData.localBlockCounter++;
    }
    else{
        // ApplicationError InvalidTransferId
    }
    return result;

}

ara::ucm::pkgmgr::PackageManagement::TransferExitOutput PackageManagementSkeleton::TransferExit(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    ara::ucm::pkgmgr::PackageManagement::TransferExitOutput result;
    std::cout << buffer.size() << std::endl;
    SaveBlock("/home/bassant/Documents/GitHub/Adaptive/src/ara/ucm/pkgmgr/test.zip", PackageManagementSkeleton::buffer); // gamda ya Bassant
    return result;
}


ara::ucm::pkgmgr::PackageManagement::TransferStartOutput PackageManagementSkeleton::TransferStart(uint64_t size)
{
    ara::ucm::pkgmgr::PackageManagement::TransferStartOutput result;
    TransferInfoData.localBlockCounter = 0;
    TransferInfoData.TransferExitFlag = false;
    std::shared_ptr<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>> promise = std::make_shared<std::promise<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput>>();
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> future = promise->get_future();
    uuid u;
    u = (boost::uuids::random_generator()());

    for(int i = 0; i < 16; i++){
        TransferInfoData.id[i] = u.data[i];
        result.id[i] = u.data[i];
    }

    // don't change 64 (ucm_client.cpp)
    TransferInfoData.BlockSize = 64;
    TransferInfoData.size = size;
    buffer.clear();
    result.BlockSize = TransferInfoData.BlockSize;
    
    return result;
}
