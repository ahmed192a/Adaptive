/**
 * @file package_management.cpp
 * @brief Definition of Provided Port(PackageManagement) methods
 * @version 0.1
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include <cmath>

static uint16_t current_state; /*!< variable to store the state of the bootloader updating sequence */

void SaveBlock(const char *filename, std::vector<uint8_t> &data_block)
{
    std::ofstream outfile(filename, std::ios::out | std::ofstream::app);
    outfile.write((const char *)&data_block[0], data_block.size());
    outfile.close();
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

ara::ucm::pkgmgr::PackageManagement::ActivateOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Activate()
{
    ara::ucm::pkgmgr::PackageManagement::ActivateOutput output;
    output.error = 0;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::CancelOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Cancel(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    ara::ucm::pkgmgr::PackageManagement::CancelOutput output;
    output.error = 0;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::DeleteTransfer(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput output;
    output.error = 0;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::FinishOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Finish()
{
    ara::ucm::pkgmgr::PackageManagement::FinishOutput output;
    output.error = 0;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetHistory(uint64_t timestampGE, uint64_t timestampLT)
{
    ara::ucm::pkgmgr::PackageManagement::GetHistoryOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetIdOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetId()
{
    ara::ucm::pkgmgr::PackageManagement::GetIdOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwClusterChangeInfo()
{
    ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwClusterDescription()
{
    ara::ucm::pkgmgr::PackageManagement::GetSwClusterDescriptionOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwClusterInfo()
{
    ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwPackages(ara::ucm::pkgmgr::PackageManagement::SwPackageInfoVectorType &Packages)
{
    ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::GetSwProcessProgress(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput output;
    return output;
}

std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::ProcessSwPackage(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    std::future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> f = std::async([&, id]()
                                                                                            {
        ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput result;

              //UART_receiveBlock((uint8 *)&current_state, CMD_SIZE);
    while (1) /* stay in this loop until the update is finished or canceled */
    {
        uint16_t packet_num;
        uint16_t extra_bytes;
        switch (current_state)
        {
        case RECEIVE_REQUEST_FREAME_INFO:
            //UART_receiveBlock((uint8 *)&current_state, CMD_SIZE);
            current_state = SEND_FRAME_INFO;	
            break;
        case SEND_FRAME_INFO:
        {
            int FRAME_SIZE = 4;
            int Frame [4];
            packet_num = TransferInfoData.localBlockCounter + 1;
            extra_bytes = (TransferInfoData.size % TransferInfoData.BlockSize);
            uint8_t * ex = (uint8_t *)&(extra_bytes);
            uint8_t * f = (uint8_t *)&(packet_num);
            Frame[0] = *f;
            Frame[1] = *(f+1);
            Frame[2] = *ex;
            Frame[3] = *(ex+1);
           //UART_sendBlock(Frame, FRAME_SIZE);
           //UART_receiveBlock((uint8 *)&current_state, CMD_SIZE);
           break;	
        }
        case READY_TO_SEND_UPDATE:
           //UART_receiveBlock((uint8 *)&current_state, CMD_SIZE);
           current_state = SEND_PACKET;	
           break;
        case SEND_PACKET:
        {
            int block_counter = 0;
            std::vector<uint8_t> small_data;
                for(int j=0; j<TransferInfoData.BlockSize; j++)
                {
                    if(block_counter*TransferInfoData.BlockSize + j >= buffer.size()){
                        // small_data.resize(TransferInfoData.BlockSize);
                       break;
                    }
                    else
                        small_data.push_back(buffer[block_counter*TransferInfoData.BlockSize + j]);
                }
                block_counter++;
                small_data.clear();
            if(packet_num > 0)
            {
                //UART_sendBlock(small_data, TransferInfoData.BlockSize);
                packet_num -=1;
                current_state = SEND_NEW_PACKET;
            }
            else
            {
                //UART_sendBlock(small_data, extra_bytes);
                current_state = END_OF_UPDATE;
            }
        }
        case SEND_NEW_PACKET:
            //UART_receiveBlock((uint8 *)&current_state, CMD_SIZE);
            current_state = SEND_PACKET;	
            break;
        
        case END_OF_UPDATE:
             // send activiate
             //UART_sendBlock((uint8 *)&current_state, CMD_SIZE);
             break;
        case CHECK_CANCEL_UPDATE:
        break;
        case CANCEL_UPDATE_REQUEST:
           break;
        case Activate_s:
           break;
        default:
			current_state = RECEIVE_REQUEST_FREAME_INFO; 			/* Initialize the current state */
			break;
        


        }
    }
        

        return result; });
    return f;
}

ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::RevertProcessedSwPackages()
{
    ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput output;
    return output;
}

ara::ucm::pkgmgr::PackageManagement::RollbackOutput ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::Rollback()
{
    ara::ucm::pkgmgr::PackageManagement::RollbackOutput output;
    return output;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferData(ara::ucm::pkgmgr::PackageManagement::TransferIdType id, ara::ucm::pkgmgr::PackageManagement::ByteVectorType data, uint64_t blockCounter)
{
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> f = std::async([&, id, data, blockCounter]()
                                                                                        {
        ara::ucm::pkgmgr::PackageManagement::TransferDataOutput  result;
        
        
        if (TransferInfoData.id == id)
        {
            

            if (blockCounter == TransferInfoData.localBlockCounter)
            {
            /* Check if the received block size is equal the block size returned by TransferStart for the same TransferId */

                if (data.size() == TransferInfoData.BlockSize)
                {
                    if(blockCounter == TransferInfoData.lastBlockCounter )
                    {
                        TransferInfoData.BlockSize = TransferInfoData.size % TransferInfoData.BlockSize;
                    }
                    for (int i = 0; i < TransferInfoData.BlockSize; i++)
                    {
                        buffer.push_back(data[i]);
                    }   
                    
                    struct ara::ucm::pkgmgr::PackageManagement::TransferDataOutput output = {1};
                    // result = output;
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
        else
        {
            // ApplicationError InvalidTransferId
        }
        return result; });

    return f;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferExit(ara::ucm::pkgmgr::PackageManagement::TransferIdType id)
{
    std::future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> f = std::async([&, id]()
                                                                                        {
        ara::ucm::pkgmgr::PackageManagement::TransferExitOutput result;
        std::string str(std::begin(id), std::end(id));
         str = "ucm_server/" + str + ".zip";
        SaveBlock(str.data() , this->buffer); 
        return result; });

    return f;
}

std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::TransferStart(uint64_t size)
{

    std::future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> f = std::async([&, size]()
                                                                                         {
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
        
        TransferInfoData.lastBlockCounter = ceil((double)TransferInfoData.size / TransferInfoData.BlockSize) - 1;

        return result; });
    return f;
}
