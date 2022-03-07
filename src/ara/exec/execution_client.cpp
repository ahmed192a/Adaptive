/**
 * @file execution_client.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "execution_client.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include <fcntl.h>
#include "unistd.h"

#include <iostream>
namespace ara
{
    namespace exec
    {
        ExecutionClient::ExecutionClient() noexcept
        {
            // // opens the Execution Management communication channel for reporting the Execution State
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
            if(fd == -1) {
                std::cout<< "[ERROR] => can't open fifo";
            }
        }
        ExecutionClient::~ExecutionClient()
        {
            // close file descriptor
            close(fd);
        }
        void ExecutionClient::ReportExecutionState(ara::exec::ExecutionState state) const noexcept
        {
            std::string m = "run";
            if (write(fd, &state, sizeof(state)) == -1)
            {
                // TO DO
                // Log Error : counldn't send the state to fifo
            }
        }

    }
}