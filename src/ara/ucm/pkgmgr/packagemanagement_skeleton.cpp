/**
 * @file package_management.cpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of Provided Port(PackageManagement) methods
 * @version 0.1
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "ara/ucm/pkgmgr/packagemanagement_skeleton.hpp"
#include "ara/ucm/pkgmgr/uart_linux.hpp"
#include <cmath>
#include <filesystem>

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
        uart_linux u_linux;
        current_state = trigger_seq;
        uint16_t packet_num;
        uint16_t extra_bytes;
        int block_counter = 0;
        std::vector<uint8_t> data_block(buffer.begin()+52, buffer.end());
        printf("first address %x\n", *((uint32_t *)data_block.data()));
        packet_num = (uint32_t)(data_block.size() /0x400) ;
        extra_bytes = (data_block.size()% 0x400);

        std::cout<<"buffer size " << buffer.size()<< std::endl;
        std::cout<<"buffer size " << data_block.size()<< std::endl;
        std::cout<<"packet_num "<<packet_num<<std::endl;
        std::cout<<"extra_bytes "<< extra_bytes<<std::endl;
        
    while (1) /* stay in this loop until the update is finished or canceled */
    {
        switch (current_state)
        {

            case trigger_seq:
            {
                cout<<"Tig"<<endl;
                std::vector<uint8_t> start ;
                start.push_back('s');
                int st = start.size();
                u_linux.UART_sendBlock(start.data(),st);
                u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
                std::cout<<"receive seq"<<endl;
                cout<<endl;
                // if(current_state == 1) current_state = trigger_seq;
                break;
            }
            case 2:
            {
                // sleep(1);
                u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
                printf("Received command : %x\n", current_state);
                break;
            }
            case RECEIVE_REQUEST_FREAME_INFO:
            {
                int FRAME_SIZE = 4;
                uint8_t Frame [4];

                Frame[0] = uint8_t (packet_num&0x00FF);
                Frame[1] = uint8_t ((packet_num&0xFF00)>>8);
                Frame[2] = uint8_t (extra_bytes&0x00FF);
                Frame[3] = uint8_t ((extra_bytes&0xFF00)>>8);
                
                u_linux.UART_sendBlock(Frame, FRAME_SIZE);

                std::cout<<"SEND_FRAME_INFO  "<<endl;
                current_state = 2;
            break;	
            }
            case SEND_NEW_PACKET:
            {
                
                std::vector<uint8_t> small_data;
                for(int j=0; j<0x400; j++)
                {
                    if((block_counter*0x400)+ j < data_block.size()){
                        small_data.push_back(data_block[block_counter*0x400 + j]);
                    }else
                        break;
                }
                u_linux.UART_sendBlock(small_data.data(), small_data.size());

                
                std::cout<<"\t->SEND Packet : "<< block_counter <<" Packet size "<< small_data.size()<<std::endl;
                packet_num -=1;
                block_counter++;

                small_data.clear();
                current_state = 2;
                break;
            }
            case END_OF_UPDATE:
            {
                std::cout<<"END_OF_UPDATE "<<endl;
                printf("%x\n", current_state);
                current_state = Activate_s;
                u_linux.UART_sendBlock((uint8_t *)&current_state, CMD_SIZE);
                std::cout<<"Activate ";
                printf("%x", current_state);     
                cout<<endl;
                break;
            }
            case Activate_s:
            {   
                u_linux.UART_receiveBlock((uint8_t *)&current_state, CMD_SIZE);
                std::cout<<"Recieved UPDATE_SUCCESS : ";
                printf("%x", current_state);
                cout<<endl;

            break;
            }

            default:
            {
                current_state = 2; 			/* Initialize the current state */
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
                    if(blockCounter == TransferInfoData.lastBlockCounter)
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
                    /* ApplicationError IncorrectBlockSize -> Too big block size received by UCM */
                    /* In case the received block size with TransferData */
                    /* exceeds the block size returned by TransferStart for the same TransferId */
                }
            }
            else
            {
                /* ApplicationError BlockInconsistent */
                /* ApplicationError IncorrectBlock    */
            }
            TransferInfoData.localBlockCounter++;
        }
        else
        {
            /* ApplicationError InvalidTransferId   */
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
        /*   convert std::array<uint8_t, 16> to string    */
        for(int i =0 ; i<16;i++){
            str += " ";
            snprintf(&str[i], 4, "%d", id[i]);
        }  
        // check if folder SWP doesn't exists
        if(!std::filesystem::exists("./SWP"))
        {
            std::filesystem::create_directory("./SWP");
        } 
        str = "SWP/" + str + ".out";
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

void ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
{
    // extract event id
    uint16_t event_id = message.MessageId().method_id & 0x7FFF;
    switch (event_id)
    {
    case 0:                                                                  /* Id of CurrentStatus Field   */
        if (message.Length() > ara::com::SOMEIP_MESSAGE::Header::HeaderSize) /* if Message has payload So it's Set request with the new data  */
        {
            /*    CurrentStatus does't have setter   */
            NoMethodHandler(event_id, cserver); /* Send Error Message unknown event_id  */
        }
        else // if Message doesn't have payload So it's Get request with just the header 16 Bytes
        {
            CurrentStatus.HandleGet(message, cserver);
        }
        break;
    default:
        NoMethodHandler(event_id, cserver); // Send Error Message unknown event_id
        break;
    }
}

void ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton::method_dispatch(ara::com::SOMEIP_MESSAGE::Message &message, Socket &cserver)
{
    ara::com::Deserializer dser;

    uint16_t methodID = message.MessageId().method_id;

    cout << "\t --------------------------------------------------------------------------- " << endl;

    cout << "\t[SERVER] Dispatch " << methodID << endl;

    switch (methodID)
    {
    case 7: // TransferStart
        HandleCall(*this, &PackageManagementSkeleton::TransferStart, message, cserver);

        break;
    case 8: // TransferData
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
            ara::com::SOMEIP_MESSAGE::Message_ID{(uint16_t)this->UCM_Service_id, (uint16_t)(message.MessageId().method_id & 0x7fff)},
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
        NoMethodHandler(methodID, cserver); // Send Error Message unknown method
        // cserver.Send(&result, sizeof(int));
        // cserver.CloseSocket();
        break;
    }
}