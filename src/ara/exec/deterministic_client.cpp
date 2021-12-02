#include "deterministic_client.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include <fcntl.h>
#include "utility"
#include <vector>
namespace ara
{
    namespace exec
    {
        DeterministicClient::DeterministicClient()
        {
            // opens the Execution Management communication channel to access a wait point for cyclic execution
            if (mkfifo(fifo_l, 0777) == -1)
            {
                if (errno != EEXIST)
                {
                    // TO DO
                    // Log Error : coundn't create fifo
                }
            }
            // get file discreptor
            fd = open(fifo_l, O_WRONLY);
        }
        DeterministicClient::~DeterministicClient()
        {
            // close file descriptor
            close(fd);
        }

        template <typename ValueType, typename Container>
        void RunWorkerPool(WorkerRunnable<ValueType> &runnableObj, Container &container) noexcept
        {
            //std::array<WorkerThread, 4> workers;
            // template <typename C>
            // void DeterministicClient::RunWorkerPool(WorkerRunnable<typename C::value_type> &w, C &container) noexcept
            // {
            int count = 0;
            auto c = container.begin();
            while (c != container.end())
            {
                w.Run(*c++, workers[count++]);
                count %= workers.size();
            }
            // }
        }

        /*ara::core::Result<ActivationReturnType>*/ std::string WaitForActivation() noexcept
        {
        }
        uint64_t GetRandom() noexcept
        {
                }
        void SetRandomSeed(uint64_t seed) noexcept
        {
        }

        /*ara::core::Result<DeterministicClient::TimeStamp>*/ std::string GetActivationTime() noexcept
        {
        }

        /*ara::core::Result<DeterministicClient::TimeStamp>*/ std::string GetNextActivationTime() noexcept
        {
        }

    } // namespace exec

} // namespace ara
