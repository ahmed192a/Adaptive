/**
 * @file worker_runnable.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definitions of the WorkerRunnable class
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_EXEC_WORKER_RUNNABLE_H_
#define ARA_EXEC_WORKER_RUNNABLE_H_

#include "ara/exec/worker_thread.h"

namespace ara
{
    namespace exec
    {
        template <typename ValueType>

        /**
         * @brief Base-class for implementation of worker runnable for Deterministic Client.
         * 
         */
        class WorkerRunnable
        {
        public:
            /**
             * @brief Deterministic client worker runnable.
             * 
             * @param element 
             * @param t 
             */
            virtual void Run(ValueType &element, ara::exec::WorkerThread &t) = 0;

            /**
             * @brief Destroy the Worker Runnable object
             * 
             */
            virtual ~WorkerRunnable();
        };
    } // namespace exec

} // namespace ara

#endif
