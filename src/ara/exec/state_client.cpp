/**
 * @file state_client.cpp
 * @author Flashing Adapter Graduation Project Team
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
#include <future>
#include <iostream>

namespace ara
{
    namespace exec
    {
        StateClient::StateClient() noexcept
        {
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
        StateClient::~StateClient() noexcept
        {
            // close file descriptor
            close(fd);
        }

        std::future<boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc>> StateClient::SetState(FunctionGroupState const &state) const noexcept
        {
            std::future<boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc>> _future;
            _future = std::async([&]()
            {
                boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc> _variant;                                      
                std::string msg = state.get_FGname() + "/" + state.get_states();
                std::cout<<"StateClient::SetState : "<<msg<<std::endl;
                if (write(fd, &msg[0], msg.size()) == -1)
                {
                    _variant.emplace<1>(ara::exec::ExecErrc::kCommunicationError);
                    return _variant;
                }
                _variant.emplace<0>();
                return _variant;
            });

            return _future;
        }

        // ara::core::Future<void>
        std::future<boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc>> StateClient::GetInitialMachineStateTransitionResult() const noexcept
        {
            std::future<boost::variant2::variant<boost::variant2::monostate, ara::exec::ExecErrc>> _future;
            return _future;
        }

    } // namespace exec

} // namespace ara