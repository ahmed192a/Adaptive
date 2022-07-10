/**
 * @file worker_thread.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of the WorkerThread class
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
        /**
         * @brief Class to implement worker thread for Deterministic Client 
         * 
         */
        class WorkerThread
        {
        public:
            /**
             * @brief Construct a new Worker Thread instance
             * 
             */
            WorkerThread(){}

            /**
             * @brief Returns a deterministic pseudo-random number which is unique for each container element.
             * 
             * @return uint64_t 
             */
            uint64_t GetRandom() noexcept{ return 0;}

            /**
             * @brief Destroy the Worker Thread object
             * 
             */
            virtual ~WorkerThread(){}
        };
    } // namespace exec

} // namespace ara

#endif
