/**
 * @file SomeipSDMessage.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SOMEIPSDMESSAGE_H
#define SOMEIPSDMESSAGE_H

#include <stdint.h>
#include <vector>
#include <memory>
#include <utility>
#include "ara/com/SOMEIP/Message.hpp"
#include "ara/com/SOMEIP/entry/entry.hpp"
#include "ara/com/SOMEIP/entry/service_entry.hpp"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"

namespace ara
{
    namespace com
    {
        namespace SOMEIP_MESSAGE
        {
            namespace sd
            {
               
                class SomeIpSDMessage : public Message
                {
                private:
                	static constexpr struct Request_ID RID={.client_id =0, .session_id=1 };
					static constexpr struct Message_ID MID={0xffff,0x8100};
                    static const uint8_t ProtocolVersion = 0x01;
                    static const uint8_t InterfaceVersion = 0x01;
                    static const MessageType Messagetype = MessageType::NOTIFICATION;

                    bool Rebooted =false;
                    std::vector<entry::Entry *> entries;

                    uint32_t getEntriesLength() const noexcept;
                    uint32_t getOptionsLength() const noexcept;

                public:
                    SomeIpSDMessage();

                    const std::vector<entry::Entry *> &Entries() const noexcept;

                    
                    void AddEntry(entry::Entry *entry);

                    uint32_t Length()  noexcept override;

                    void SetSessionId(uint16_t sessionId) override;

                    bool IncrementSessionId() noexcept override;

                    std::vector<uint8_t> Serializer()  override;

                    void Deserialize(const std::vector<uint8_t> &payload);


                    // void setdata(std::vector<uint8_t> data) {
                    //     uint32_t mlength = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
                    //     mlength -= 3*4;
                    //     uint32_t elenght = data[20] << 24 | data[21] << 16 | data[22] << 8 | data[23];
                    //     for(int i = 0; i < elenght/16; i+=1)
                    //     {
                    //         uint8_t entry_type = data[16*i + 24];
                    //         uint16_t serivce_id = data[16*i + 28] << 8 | data[16*i + 29];
                    //         uint16_t instanceId = data[16*i + 30] << 8 | data[16*i + 31];
                    //         uint8_t majorVersion = data[16*i + 32];
                    //         uint32_t ttl = data[16*i + 33] << 16 | data[16*i + 34] << 8 | data[16*i + 35];
                    //         uint32_t minorVersion = data[16*i + 36] << 24 | data[16*i + 37] << 16 | data[16*i + 38] << 8 | data[16*i + 39];

                    //         switch(entry_type)
                    //         {
                    //             case 0x00:
                    //                 entries.push_back(std::make_shared<entry::ServiceEntry>(entry::ServiceEntry::CreateFindServiceEntry (serivce_id,ttl,instanceId,majorVersion ,minorVersion)).get());
                    //                 break;
                    //             case 0x01:
                    //                 entries.push_back(std::make_shared<entry::ServiceEntry>(entry::ServiceEntry::CreateOfferServiceEntry (serivce_id,instanceId,majorVersion ,minorVersion,ttl)).get());
                    //                 break;
                    //             case 0x02:
                    //                 entries.push_back(std::make_shared<entry::ServiceEntry>(entry::ServiceEntry::CreateStopOfferEntry (serivce_id,instanceId,majorVersion ,minorVersion)).get());
                    //                 break;
                    //             default:
                    //                 break;
                    //         }
                            
                    //         uint8_t index_first_option = data[16*i + 25];
                    //         uint8_t index_seconde_option = data[16*i + 26];
                    //         uint8_t c_option = data[16*i + 27];
                    //         uint32_t ptr2=elenght +24 +4, ptr1 = elenght +24 +4;
                    //         if(c_option &0x0F)
                    //         {
                    //             while(index_seconde_option--)
                    //             {
                    //                 uint16_t osize = data[ptr2] << 8 | data[ptr2+1];
                    //                 ptr2+=osize+3;
                    //             }
                    //             for(int j = 0; j < (c_option &0x0F); j++)
                    //             {
                    //                 uint16_t osize = data[ptr2] << 8 | data[ptr2+1];
                    //                 uint8_t Ipv4EndpointOption_type = data[ptr2+2];
                    //                 switch(Ipv4EndpointOption_type)
                    //                 {
                    //                     case 0x04:
                    //                         entries[i]->AddFirstOption(std::make_shared<option::Ipv4EndpointOption>(option::Ipv4EndpointOption::CreateSdEndpoint(false,ara::com::helper::Ipv4Address(data[ptr2+4],data[ptr2+5],data[ptr2+6],data[ptr2+7]),(ara::com::option::Layer4ProtocolType)data[ptr2+9],data[ptr2+10] << 8 | data[ptr2+11])).get());
                    //                         break;
                    //                     default:
                    //                         break;
                    //                 }
                    //                 ptr2+=osize+3;
                                    
                    //             }
                    //         }
                    //         if((c_option&0xF0) >> 4)
                    //         {
                    //             while(index_first_option--)
                    //             {
                    //                 uint16_t osize = data[ptr1] << 8 | data[ptr1+1];
                    //                 ptr1+=osize+3;
                    //             }
                    //             for(int j = 0; j < ((c_option&0xF0) >> 4); j++)
                    //             {
                    //                 uint16_t osize = data[ptr1] << 8 | data[ptr1+1];
                    //                 uint8_t Ipv4EndpointOption_type = data[ptr1+2];
                    //                 switch(Ipv4EndpointOption_type)
                    //                 {
                    //                     case 0x04:
                    //                         entries[i]->AddFirstOption(std::make_shared<option::Ipv4EndpointOption>(option::Ipv4EndpointOption::CreateSdEndpoint(false,ara::com::helper::Ipv4Address(data[ptr1+4],data[ptr1+5],data[ptr1+6],data[ptr1+7]),(ara::com::option::Layer4ProtocolType)data[ptr1+9],data[ptr1+10] << 8 | data[ptr1+11])).get());
                    //                         break;
                    //                     default:
                    //                         break;
                    //                 }
                    //                 ptr1+=osize+3;
                                    
                    //             }
                    //         }
                    //     }


                    // }
                };
            }
        }
    }
}
#endif
