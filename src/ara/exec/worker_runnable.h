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
        

        /**
         * @brief WorkerRunnable Base-class for implementation of worker runnable for Deterministic Client.
         * @tparam ValueType type of the element to be processed by the worker thread.
         */
        template <typename ValueType>
        class WorkerRunnable
        {
        public:
            /**
             * @brief Deterministic client worker runnable.
             * 
             * @param element   element to be processed by the worker thread.
             * @param t         worker thread.
             */
            virtual void Run(ValueType &element, ara::exec::WorkerThread &t) = 0;

            /**
             * @brief Destroy the Worker Runnable object
             * 
             */
            virtual ~WorkerRunnable() = default;
        };
    } // namespace exec

} // namespace ara

#endif
