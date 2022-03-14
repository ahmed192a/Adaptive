/**
 * @file state_client.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/exec/state_client.hpp"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include <fcntl.h>
#include "unistd.h"
#include<future>
#include<iostream>

namespace ara
{
    namespace exec
    {
        StateClient::StateClient() noexcept{
            // opens the State Client communication channel 
            // if (mkfifo(fifo_l, 0777) == -1)
            // {
            //     if (errno != EEXIST)
            //     {
            //         // TO DO
            //         // Log Error : coundn't create fifo
            //     }
            // }
            // get file discreptor
            fd = open(fifo_l, O_WRONLY);
        }
        StateClient::~StateClient() noexcept{
            // close file descriptor
            close(fd);
        }

        ara::exec::ExecErrc StateClient::SetState(FunctionGroupState const &state) const noexcept{
            // std::variant<ara::exec::ExecErrc, std::future<void>> _variant;
            // std::promise<void> _promise;



            std::string msg = state.get_FGname()+"/"+state.get_states();
            std::cout<<"not set state\n";
            if (write(fd, &msg[0], msg.size()) == -1)
            {
                std::cout<<"set state\n";
                // _variant.emplace<0>( ara::exec::ExecErrc::kCommunicationError);
                // return _variant;
                return ara::exec::ExecErrc::kCommunicationError;

            }
            // _variant.emplace<1>(_promise.get_future());
            // _promise.set_value();
            return ara::exec::ExecErrc::kAlreadyInState;
        }
        
        // ara::core::Future<void> 
        void StateClient::GetInitialMachineStateTransitionResult() const noexcept{
            
        }


    } // namespace exec
    
} // namespace ara