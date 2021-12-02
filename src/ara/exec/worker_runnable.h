

#ifndef ARA_EXEC_WORKER_RUNNABLE_H_
#define ARA_EXEC_WORKER_RUNNABLE_H_

#include "ara/exec/worker_thread.h"

namespace ara
{
    namespace exec
    {
        template <typename ValueType>
        class WorkerRunnable
        {
            virtual void Run(ValueType &element, ara::exec::WorkerThread &t) = 0;
        };
    } // namespace exec

} // namespace ara

#endif
