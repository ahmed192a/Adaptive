/**
 * @file entry_deserializer.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ENTRY_DESERIALIZER_H
#define ENTRY_DESERIALIZER_H

#include "ara/com/SOMEIP/entry/entry.h"
#include "ara/com/SOMEIP/entry/eventgroup_entry.h"
#include "ara/com/SOMEIP/entry/service_entry.h"

namespace ara
{
    namespace com
    {
        namespace entry
        {
            /**
             * @brief Class Entry_Deserializer used to deserialize ara::com::entry::Entry
             * 
             */
            class Entry_Deserializer
            {
               
            public:
                /**
                 * @brief  Deserialize payload to ara::com::entry::Entry
                 * 
                 * @param payload  vector of bytes to be deserialized
                 * @param offset    offset of the payload
                 * @return Entry*   pointer to ara::com::entry::Entry
                 */
                static Entry *Deserialize(const std::vector<uint8_t> &payload, std::size_t offset) {
                    Entry *_result = nullptr;           // pointer to ara::com::entry::Entry
                    EntryType _type = static_cast<EntryType>(payload[offset]);  // type of the entry
                    offset += 4;                        // skip the type field
                    uint16_t _serviceId = (payload[offset ] << 8) | payload[offset +1];         // service id of the entry
                    uint16_t _instanceId = (payload[offset + 2] << 8) | payload[offset + 3];    // instance id of the entry
                    offset += 4;                        // skip the service id and instance id fields
                    uint8_t _majorVersion = payload[offset];                                    // major version of the entry
                    // ttl of the entry
                    uint32_t _ttl = ((payload[offset + 1] << 16) | (payload[offset + 2] << 8) | payload[offset + 3]) & 0x00FFFFFF;  
                    offset += 4;                        // skip the major version field
                    uint32_t _minorVersion  = payload[offset]<<24 | payload[offset + 1]<<16 | payload[offset + 2]<<8 | payload[offset + 3];
                    uint16_t _groupId = _minorVersion & 0x0000FFFF;                             // group id of the entry
                    switch (_type)                      // switch on the type of the entry
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