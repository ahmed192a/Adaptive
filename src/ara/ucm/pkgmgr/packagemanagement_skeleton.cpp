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

// ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput PackageManagementSkeleton::ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
// {
//     CClient c1(SOCK_STREAM);
//     c1.OpenSocket();
//     c1.GetHost("127.0.0.1", 3600);
//     c1.ClientConnect();
//     std::vector<char> Temp_data2 = ReadAllBytes2("/home/bassant/Documents/GitHub/Adaptive/src/ara/ucm/pkgmgr/test.zip");
//     int x = Temp_data2.size();
//     c1.ClientWrite((void *)&x, sizeof(int));
//     c1.ClientWrite((void *)&Temp_data2[0], x);
// }

std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> f = std::async([&]()
    {
        ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput result;

        return result;
    });
    return f;
}

ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::RevertProcessedSwPackages()
{
}
ara::ucm::pkgmgr::PackageManagement::RollbackOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Rollback()
{
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferData(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter)
{
     std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> f = std::async([&, id, data, blockCounter]()
    {
        // std::cout << "xxxx" << std::endl;
        ara::ucm::pkgmgr::PackageManagement::TransferDataOutput  result;
        
        
        if (TransferInfoData.id == id)
        {
            

            if (blockCounter == TransferInfoData.localBlockCounter)
            {
            // std::cout << "data size: " << data.size() << std::endl;
            /* Check if the received block size is equal the block size returned by TransferStart for the same TransferId */
            if (data.size() == TransferInfoData.BlockSize)
            {
                
                // uint32_t i = TransferInfoData.localBlockCounter * TransferInfoData.BlockSize;
                // copy(data.begin(), data.end(), std::back_inserter(PackageManagementSkeleton::buffer));
                for (int i = 0; i < TransferInfoData.BlockSize; i++)
                {
                    buffer.push_back(data[i]);
                }   
                // std::cout << buffer.size() << std::endl;
                
                // this if reaches last block
                // if ((TransferInfoData.localBlockCounter + 1) * TransferInfoData.BlockSize == TransferInfoData.size)
                // {    
                // }    
                //SaveBlock("/home/basmala/Desktop/Gradution_project/test1/myfile3.zip" , data);
                struct ara::ucm::pkgmgr::PackageManagement::TransferDataOutput output = {1};
                // result = output;
            }
            else
            {
                // result = ara::ucm::pkgmgr::PackageManagement::IncorrectBlockSize;
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
        else
        {
            // ApplicationError InvalidTransferId
        }
        return result;
    });

    return f;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferExit(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> f = std::async([&, id]()
    {
        ara::ucm::pkgmgr::PackageManagement::TransferExitOutput result;
        SaveBlock("ucm_server/test.zip", PackageManagementSkeleton::buffer); // gamda ya Bassant
        return result;
    });

    return f;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferStart(uint64_t size)
{
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> f = std::async([&]()
    {
        // std::cout << "size  : " << size << std::endl;
        ara::ucm::pkgmgr::PackageManagement::TransferStartOutput result;
        TransferInfoData.localBlockCounter = 0;
        TransferInfoData.TransferExitFlag = false;
        uuid u;
        u = (boost::uuids::random_generator()());
        for (int i = 0; i < 16; i++)
        {
            TransferInfoData.id[i] = u.data[i];
            result.id[i] = u.data[i];

        }
        std::cout << std::endl;
        // don't change 64 (ucm_client.cpp)
        TransferInfoData.BlockSize = 64;
        TransferInfoData.size = size;
        buffer.clear();
        result.BlockSize = TransferInfoData.BlockSize;
        return result;
    });
    return f;
}
