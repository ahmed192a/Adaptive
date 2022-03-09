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
namespace ara
{
    namespace exec
    {
        StateClient::StateClient() noexcept{
            // opens the State Client communication channel 
            if (mkfifo(fifo_l, 0777) == -1)
            {
                if (errno != EEXIST)
                {
                    // TO DO
                    // Log Error : coundn't create fifo
                }
            }
            // get file discreptor
            fd = open(fifo_l, O_WRONLY);
        }
        StateClient::~StateClient() noexcept{
            // close file descriptor
            close(fd);
        }

        // ara::core::Future<void>
        void StateClient::SetState(FunctionGroupState const &state) const noexcept{
            if (write(fd, &state, sizeof(state)) == -1)
            {
                // TO DO
                // Log Error : counldn't send the state to fifo
            }
        }
        
        // ara::core::Future<void> 
        void StateClient::GetInitialMachineStateTransitionResult() const noexcept{
            
        }


    } // namespace exec
    
} // namespace ara
