/**
 * @file worker_runnable.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_EXEC_WORKER_RUNNABLE_H_
#define ARA_EXEC_WORKER_RUNNABLE_H_

#include "worker_thread.h"

namespace ara
{
    namespace exec
    {
        template <typename ValueType>
        class WorkerRunnable
        {
        public:
            virtual void Run(ValueType &element, ara::exec::WorkerThread &t) = 0;
            virtual ~WorkerRunnable();
        };
    } // namespace exec

} // namespace ara

#endif
