#include "deterministic_client.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include "utility"
#include <vector>
// number of thread which depends on the number of core
std::array<ara::exec::WorkerThread, 4> workers;

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
            // TO DO : This part is sequential, it needs to be converted to parallel with fork()
            int count = 0;
            auto c = container.begin();
            while (c != container.end())
            {
                runnableObj.Run(*c++, workers[count++]);
                count %= workers.size();
            }
        }

        ActivationReturnType WaitForActivation() noexcept
        {
            // Blocks and returns with a process control value when the next activation is triggered by the Runtime
            char state[5];
            read(fd, state, 5 * sizeof(char));
        }
        uint64_t GetRandom() noexcept
        {
            return lrand48();
        }
        void SetRandomSeed(uint64_t seed) noexcept
        {
            srand48(seed);
        }

        DeterministicClient::TimeStamp > GetActivationTime() noexcept
        {
        }

        DeterministicClient::TimeStamp > GetNextActivationTime() noexcept
        {
        }

    } // namespace exec

} // namespace ara
