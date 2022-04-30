/**
 * @file event.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/com/proxy_skeleton/skeleton/event.hpp"

void (*g_handler)(int, siginfo_t *, void *);

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {
                namespace EVENT
                {
                    /**
                     * @brief Set the handle object
                     * 
                     * @param handler 
                     */
                    void set_handle(void (*handler)(int, siginfo_t *, void *))
                    {
                        struct sigaction signal_action;
                        signal_action.sa_sigaction = handler;
                        sigemptyset(&signal_action.sa_mask);
                        signal_action.sa_flags = SA_SIGINFO;
                        sigaction(SIGUSR1, &signal_action, NULL);
                    }
                } // namespace EVENT

            } // namespace skeleton

        } // namespace proxy_skeleton

    } // namespace com

} // namespace ara
