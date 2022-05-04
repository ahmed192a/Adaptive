/**
 * @file package_management.cpp
 * @brief Definition of Provided Port(PackageManagement) methods
 * @version 0.1
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include "ara/ucm/pkgmgr/uart_linux.hpp"
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
        bool found = false;
        uart_linux u_linux;
        current_state = trigger_seq;
        uint16_t packet_num;
        uint16_t extra_bytes;
        int block_counter = 0;
        packet_num = (uint32_t)(TransferInfoData.size /0x400) ;
        extra_bytes = (TransferInfoData.size % 0x400);

        std::cout<<"buffer size " << buffer.size()<< std::endl;
        std::cout<<"buffer size " << TransferInfoData.size<< std::endl;
        std::cout<<"extra_bytes "<<packet_num<<std::endl;
        std::cout<<"extra_bytes "<< extra_bytes<<std::endl;
        

              //UART_receiveBlock((uint8 *)&current_state, CMD_SIZE);
    while (1) /* stay in this loop until the update is finished or canceled */
    {
        if(found == true)
        {
            std::cout<<"found"<<std::endl;
            std::cout<<"current_state ";
            printf("%x\n", current_state);
            found = false;
        }
        switch (current_state)
        {
            case trigger_seq:
            {
                std::vector<uint8_t> start ;
                start.push_back('s');
                int st = start.size();
                u_linux.UART_sendBlock(start.data(),st);
                // std::cout<<"trigger seq\n";
                // current_state = 1;
                // sleep(3);
                // std::cout<<"Finish delay 3s\n";
                u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
                std::cout<<"receive seq\n";
                printf("COMAAND : %x\n", current_state);
                if(current_state == 1) current_state = trigger_seq;
                break;
            }
            case 2:
            {
                u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
                printf("COMAAND : %x\n", current_state);
                if(current_state == 0x7777) found = true;
                break;
            }
            case RECEIVE_REQUEST_FREAME_INFO:
            {
                int FRAME_SIZE = 4;
                int Frame [4];

                uint8_t * ex = (uint8_t *)&(extra_bytes);
                uint8_t * f = (uint8_t *)&(packet_num);
                cout<<"1 "<<(uint16_t) *f<< " "<<(uint16_t) *(f+1)<<endl;
                Frame[0] = *f;
                Frame[1] = *(f+1);
                Frame[2] = *ex;
                Frame[3] = *(ex+1);
                
                u_linux.UART_sendBlock(Frame, FRAME_SIZE);
                std::cout<<"SEND_FRAME_INFO  \n";
                current_state = 2;
                // u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
            break;	
            }
            case SEND_NEW_PACKET:
            {
                
                std::vector<uint8_t> small_data;
                for(int j=0; j<0x400; j++)
                {
                    // if(block_counter*TransferInfoData.BlockSize + j >= buffer.size()){
                    //     // small_data.resize(TransferInfoData.BlockSize);
                    //    break;
                    // }
                    // else
                    if((block_counter*0x400)+ j < buffer.size()){
                        small_data.push_back(buffer[block_counter*0x400 + j]);
                    }else
                        break;
                }
                if(small_data.size() == 0x400)
                {
                    u_linux.UART_sendBlock(small_data.data(), small_data.size());
                }else{
                    u_linux.UART_sendBlock(small_data.data(), small_data.size());
                }

                
                std::cout<<"SEND Packet : "<< block_counter <<std::endl;
                packet_num -=1;
                block_counter++;

                small_data.clear();
                current_state = 2;
                std::cout<<"SEND Packet CMD : "<< current_state<<std::endl;
                break;
            }
            case END_OF_UPDATE:
            {
                current_state = Activate_s;
                u_linux.UART_sendBlock((uint8_t *)&current_state, CMD_SIZE);
                break;
            }
            case Activate_s:
            {
            u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
            break;
            }
            default:
            {
                current_state = trigger_seq; 			/* Initialize the current state */
                break;
            }
        }
        if(current_state == UPDATE_SUCCESS) break;
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
        std::string str;
        //convert std::array<uint8_t, 16> to string
        for(int i =0 ; i<16;i++){
            str += " ";
            snprintf(&str[i], 4, "%d", id[i]);
        }   
         str = "ucm_server/" + str + ".out";
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
