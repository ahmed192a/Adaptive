#ifndef ARA_EXEC_WORKER_THREAD_H_
#define ARA_EXEC_WORKER_THREAD_H_
#include <cstdint>
namespace ara
{
    namespace exec
    {
        class WorkerThread
        {
        public:
            WorkerThread();
            virtual ~WorkerThread();
            uint64_t GetRandom() noexcept;
        };
    } // namespace exec

} // namespace ara

#endif
