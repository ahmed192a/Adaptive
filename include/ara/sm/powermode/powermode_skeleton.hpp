/**
 * @file powermode_skeleton.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include "powermode_return_types.hpp"
#include "powermode_types.hpp"
#include "./powermode.hpp"

//include the file which contains this definitions


namespace ara
{
    namespace sm
    {
        namespace powermode
        {
            namespace skeleton
            {

                class PowerMode : public ara::com::proxy_skeleton::skeleton::ServiceSkeleton
                {
                public:
                    PowerMode(ara::com::InstanceIdentifier instance, ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
                        : serviceid(53), ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle)
                    {
                    }
                    ~PowerMode();
                    /*sends PowerModeMsg defined in 9.1 Type definition to all Processes to request a PowerMode.
                     *Message to all running Processes in the system to indicate a request to enter this state.*/
                    std::future<ara::sm::powermode::MessagePowermodeOutput> MessagePowerMode(PowerModeMsg msg);
                    /*ResponseMessage from a Processes which received PowerMode request from State Management.*/
                    std::future<ara::sm::powermode::EventPowermodeOutput> MessagePowerMode(PowerModeRespMsg respMsg);

                    void method_dispatch(std::vector<uint8_t> &message, Socket &cserver)
                    {
                        ara::com::Deserializer dser;
                        int methodID = dser.deserialize<int>(message, 0);
                        int result = -1;
                        cout << "\t[SERVER] Dispatch " << methodID << endl;
                        std::vector<uint8_t> msg;
                        msg.insert(msg.begin(), message.begin() + sizeof(int), message.end());

                        switch (methodID)
                        {
                        case 0:
                            //HandleCall(*this, &PowerMode::MessagePowerMode, msg, cserver);
                            break;
                        case 1:
                            //HandleCall(*this, &PowerMode::EventPowerMode, msg, cserver);
                           
                            break;

                        default:
                            cserver.Send(&result, sizeof(int));
                            cserver.CloseSocket();
                            break;
                        }
                    }

                private:
                    ara::com::InstanceIdentifier serviceid;
                };
            }
        }
    }
}