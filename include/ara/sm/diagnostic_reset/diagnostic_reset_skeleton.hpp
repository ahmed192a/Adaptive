/**
 * @file diagnostic_reset_skeleton.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "ara/com/proxy_skeleton/skeleton/field.hpp"
#include "ara/com/proxy_skeleton/proxy/service_skeleton.hpp"

#include "ara/sm/diagnostic_reset/diagnostic_reset_return_types.hpp"

#include <future>

namespace ara
{
    namespace sm
    {
        namespace diagnostic_reset
        {
            namespace skeleton
            {
                class diagnostic_reset
                {
                private:
                    struct sockaddr_in cliaddr;
                    ara::com::InstanceIdentifier serviceid;
                public:
                    

                    diagnostic_reset(
                        ara::com::InstanceIdentifier instance, 
                        ara::com::proxy_skeleton::Skeleton::ServiceSkeleton::SP_Handle skeleton_handle)
                        : ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid,instance,skeleton_handle),
                        serviceid(14)
                        {}
                    ~diagnostic_reset();

                    /*sends DiagnosticResetMsg defined in 9.1 Type definition to all Processes in a SoftwareCluster.*/
                    std::future<ara::sm::diagnostic_reset::MessageDiagnosticOutput> message();

                    /*All Processes which got a DiagnosticReset request sends this as answer to State Management*/
                    std::future<ara::sm::diagnostic_reset::EventDiagnosticOutput> event();

                   void skeleton::method_dispatch(std::vector<uint8_t>& message, Socket& cserver)
                   {
                        ara::com::Deserializer dser;
                        int methodID = dser.deserialize<int>(message,0);
                        cout<<"\t[SERVER] Dispatch " << methodID << endl;
                        std::vector<uint8_t> msg;
                        msg.insert(msg.begin(), message.begin()+sizeof(int), message.end());


                        if (methodID == 0)
                        {
                            HandleCall(*this, &diagnostic_reset::message, msg, cserver);
                        }
                        else if (methodID == 1)
                        {
                            HandleCall(*this, &diagnostic_reset::event, msg, cserver);
                        }
                        else
                        {
                            int result = -1;
                            cserver.SendServer(&result, sizeof(int));
                            cserver.ClientClose();
                        }
                   }

                    
                };
            }
        }
    }
}