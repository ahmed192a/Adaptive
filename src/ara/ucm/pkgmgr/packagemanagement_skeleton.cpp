/**
 * @file package_management.cpp
 * @brief Definition of Provided Port(PackageManagement) methods
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"


void SaveBlock(const char *filename, std::vector<uint8_t> &data_block)
{
    std::ofstream outfile(filename, std::ios::out | std::ofstream::app);
    outfile.write((const char *)&data_block[0], data_block.size());
    outfile.close();
}

ara::ucm::pkgmgr::PackageManagement::ActivateOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Activate()
{
 
}

ara::ucm::pkgmgr::PackageManagement::CancelOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Cancel(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{

}

ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::DeleteTransfer(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
 
}

ara::ucm::pkgmgr::PackageManagement::FinishOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Finish()
{

}

ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetHistory(uint64_t timestampGE, uint64_t timestampLT)
{

}

ara::ucm::pkgmgr::PackageManagement::GetIdOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetId()
{

}

ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput  ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwClusterChangeInfo()
{

}

ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwClusterDescription()
{

}

ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwClusterInfo()
{

}

ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwPackages(ara::ucm::pkgmgr::PackageManagement::SwPackageInfoVectorType &Packages)
{
  
}

ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
   
}

std::vector<char> ReadAllBytes2(char const *filename)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);
    return result;
}

ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    CClient c1(SOCK_STREAM);
    c1.OpenSocket();
    c1.GetHost("127.0.0.1", 3600);
    c1.ClientConnect();
    std::vector<char> Temp_data2 = ReadAllBytes2("/home/bassant/Documents/GitHub/Adaptive/src/ara/ucm/pkgmgr/test.zip");
    int x = Temp_data2.size();
    c1.ClientWrite((void *)&x, sizeof(int));
    c1.ClientWrite((void *)&Temp_data2[0], x);

}

ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::RevertProcessedSwPackages()
{
   
}
ara::ucm::pkgmgr::PackageManagement::RollbackOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Rollback()
{
    
}

ara::ucm::pkgmgr::PackageManagement::TransferDataOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferData(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter)
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

ara::ucm::pkgmgr::PackageManagement::TransferExitOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferExit(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    ara::ucm::pkgmgr::PackageManagement::TransferExitOutput result;
    std::cout << buffer.size() << std::endl;
    SaveBlock("/home/bassant/Documents/GitHub/Adaptive/src/ara/ucm/pkgmgr/test.zip", PackageManagementSkeleton::buffer); // gamda ya Bassant
    return result;
}


ara::ucm::pkgmgr::PackageManagement::TransferStartOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferStart(uint64_t size)
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
