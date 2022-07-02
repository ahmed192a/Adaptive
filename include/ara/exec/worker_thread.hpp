/**
 * @file worker_thread.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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
            WorkerThread(){}
            uint64_t GetRandom() noexcept{ return 0;}
            virtual ~WorkerThread(){}
        };
    } // namespace exec

} // namespace ara

#endif
