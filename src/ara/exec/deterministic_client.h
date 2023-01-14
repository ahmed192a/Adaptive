/**
 * @file deterministic_client.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of the DeterministicClient class
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_EXEC_DETERMINISTIC_CLIENT_H_
#define ARA_EXEC_DETERMINISTIC_CLIENT_H_

#include <cstdint>
#include <chrono>
#include <vector>
#include "ara/exec/worker_runnable.h"
#include <string>
#include <array>
#include <ctime>
using namespace std::literals; // enables the usage of 24h, 1ms, 1s instead of

namespace ara
{
    namespace exec
    {
        // SWS_EM_02201
        /**
         * Defines the return codes for WaitForNextActivation operations. Scoped Enumeration of uint8_t .
         */
        enum class ActivationReturnType : uint8_t
        {
            kRegisterServices = 0, // application shall register communication
                                   // services(this must be the only occasion for
                                   // performing service registering)
            kServiceDiscovery = 1, // application shall do communication service
                                   // discovery (this must be the only occasion for
                                   // performing service discovery)
            kInit = 2,             // application shall initialize its proxy_skeleton data structures
                                   // (once)
            kRun = 3,              // application shall perform its normal operation
            kTerminater = 4,       // application shall terminate

        };

        // SWS_EM_02202
        /**
         * Defines the return codes for "get activation timestamp" operations. Scoped Enumeration of uint8_t .
         */
        enum class ActivationTimeStampReturnType : uint8_t
        {
            kSuccess = 0,
            kNotAvailable = 1,
        };

        // SWS_EM_02210
        /**
         * Class to implement operations on Deterministic Client .
         */
        class DeterministicClient
        {
        private:
            // location of FIFO to communicate between EM & SM
            char fifo_l[30] = "deterministic_client_fifo";
            // index of File descriptor
            int fd;

        public:
            // using TimeStamp = std::chrono::time_point<ara::core::SteadyClock>;

            using TimeStamp = std::chrono::time_point<std::chrono::system_clock>;

            TimeStamp Activated;

            // using Worker = ara::exec::WorkerRunnable;

            // SWS_EM_02211
            /**
             * Constructor for DeterministicClient which opens the Execution Management communication
             * channel (e.g. POSIX FIFO) to access a wait point for cyclic execution, a worker pool,
             * deterministic random numbers and time stamps .
             */
            DeterministicClient() noexcept;

            // SWS_EM_02215
            /**
             * Destructor of the Deterministic Client instance .
             */
            ~DeterministicClient() noexcept;

            // SWS_EM_02217
            /**
             * Blocks and returns with a process control value when the next activation is triggered by the
             * Runtime.
             *
             * \return      ara::core::Result< ActivationReturnType >    process control value or error
             */
            ActivationReturnType WaitForActivation() noexcept;

            // SWS_EM_02221
            /**
             * @brief
             * Run a deterministic worker pool.
             * Uses a pool of Deterministic workers to call a method WorkerRunnable::Run for every element
             * of the container. The sequential iteration is guaranteed by using the container’s increment
             * operator. The API provides the guarantee that no other iteration scheme is used.
             * This function shall not participate in overload resolution unless unless ValueType is compatible
             * with Container::value_type.
             *
             * \tparam ValueType            Element type Container
             *
             * \tparam Container            Container for which method WorkerRunnable::Run is invoked for each element
             *
             * \param[in]   runnableObj     Object derived from WorkerRunnable that provides
             *                              a method called Run(...), which will be called on
             *                              every container element
             * \param[in]   container       C++ container which supports a standard iterator
             *                              interface with - begin() - end() - operator*()
             *                              operator++
             *
             * \return void
             */
            template <typename ValueType, typename Container>
            void RunWorkerPool(WorkerRunnable<ValueType> &runnableObj, Container &container) noexcept;

            // SWS_EM_02225
            /**
             * This returns ‘Deterministic’ random numbers. Deterministic’ means, that the returned random
             * numbers are identical within redundant DeterministicClient::WaitForNextActivation() cycles,
             * which are used within redundantly executed Process .
             *
             * \return uint64_t     uint64_t 64 bit uniform distributed pseudo random
             *                      number
             */
            uint64_t GetRandom() noexcept;

            // SWS_EM_02226
            /**
             * Seed random number generator used for redundantly executed deterministic clients.
             *
             * \param[in] uint64_t
             */
            void SetRandomSeed(uint64_t seed) noexcept;

            // SWS_EM_02231
            /**
             * @brief
             * TimeStamp of activation point.
             * This method provides the timestamp that represents the point in time when the activation was
             * triggered by DeterministicClient::WaitForNextActivation() with return value kRun. Subsequent
             * calls within an activation cycle will always provide the same value. The same value will also be
             * provided within redundantly executed Processes
             *
             *
             * \return      ActivationTimeStampReturnType
             *
             * \exception   noexcept
             */
            TimeStamp GetActivationTime() noexcept;
            // ActivationTimeStampReturnType GetActivationTime(TimeStamp) const noexcept;

            // SWS_EM_02236
            /**
             * @brief
             * Timestamp of next activation point.
             *
             * This method provides the timestamp that represents the point in time when the next activation
             * will be triggered by DeterministicClient::WaitForNextActivation() with return value kRun.
             * Subsequent calls within an activation cycle will always provide the same value. The same value
             * will also be provided within redundantly executed Process
             *
             *
             * \return      <ara::core::Result< TimeStamp >      TimeStamp of next activation cycle
             */
            TimeStamp GetNextActivationTime() noexcept;

            // ActivationTimeStampReturnType GetNextActivationTime(TimeStamp) const noexcept;
        };
    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_DETERMINISTIC_CLIENT_H_