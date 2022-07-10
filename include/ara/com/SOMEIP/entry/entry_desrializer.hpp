/**
 * @file entry_deserializer.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief 
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ENTRY_DESERIALIZER_H
#define ENTRY_DESERIALIZER_H

#include "ara/com/SOMEIP/entry/entry.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include "ara/com/SOMEIP/entry/service_entry.hpp"

namespace ara
{
    namespace com
    {
        namespace entry
        {
       
            class Entry_Deserializer
            {
            private:
               

            protected:
               
            public:
                static Entry *Deserialize(const std::vector<uint8_t> &payload, std::size_t offset) {
                    Entry *_result = nullptr;
                    EntryType _type = static_cast<EntryType>(payload[offset]);
                    offset += 4;
                    uint16_t _serviceId = (payload[offset ] << 8) | payload[offset +1];
                    uint16_t _instanceId = (payload[offset + 2] << 8) | payload[offset + 3];
                    offset += 4;
                    uint8_t _majorVersion = payload[offset];
                    uint32_t _ttl = ((payload[offset + 1] << 16) | (payload[offset + 2] << 8) | payload[offset + 3]) & 0x00FFFFFF;
                    offset += 4;
                    uint32_t _minorVersion  = payload[offset]<<24 | payload[offset + 1]<<16 | payload[offset + 2]<<8 | payload[offset + 3];
                    uint16_t _groupId = _minorVersion & 0x0000FFFF;
                    switch (_type)
                    {
                    case EntryType::Finding:
                        _result = new ServiceEntry(EntryType::Finding, _serviceId, _instanceId, _ttl, _majorVersion, _minorVersion);
                        break;
                    case EntryType::Offering:
                        _result = new ServiceEntry(EntryType::Offering, _serviceId, _instanceId, _ttl, _majorVersion, _minorVersion);

                        break;
                    case EntryType::Subscribing:

                        _result = new EventgroupEntry(EntryType::Subscribing, _serviceId, _instanceId, _ttl, _majorVersion, _groupId);
                        
                        break;
                    case EntryType::Acknowledging:
                        _result = new EventgroupEntry(EntryType::Acknowledging, _serviceId, _instanceId, _ttl, _majorVersion, _groupId);
                        break;
                    default:
                        
                        break;
                    }
                    return _result;
                }

                

     
            };
        }
    }
}

#endif