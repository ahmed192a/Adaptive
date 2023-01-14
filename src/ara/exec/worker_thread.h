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
#include <chrono>
#include <thread>
namespace ara
{
    namespace exec
    {
        /**
         * @brief WorkerThread Class to implement worker thread for Deterministic Client 
         * 
         */
        class WorkerThread
        {
        private:
            std::thread thread_;  /*!<  thread_ to represent the worker thread */
        public:
            /**
             * @brief Construct a new Worker Thread instance
             * 
             */
            WorkerThread()
            {
                thread_ = std::thread();
            }



            /**
             * @brief Returns a deterministic pseudo-random number which is unique for each container element.
             * 
             * @return uint64_t 
             */
            uint64_t GetRandom() noexcept{
                //generate and returns a deterministic pseudo-random number which is unique for each container element.
                return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            }

            /**
             * @brief Destroy the Worker Thread object
             * 
             */
            virtual ~WorkerThread()
            {
                //destroy the worker thread
                thread_.join();
            }
        };
    } // namespace exec

} // namespace ara

#endif
