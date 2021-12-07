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
        DeterministicClient::DeterministicClient() noexcept
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
            fd = open(fifo_l, O_RDONLY);
        }
        DeterministicClient::~DeterministicClient() noexcept
        {
            // close file descriptor
            close(fd);
        }

        template <typename ValueType, typename Container>
        void RunWorkerPool(WorkerRunnable<ValueType> &runnableObj, Container &container) noexcept
        {

            // TO DO : This part is sequential, it needs to be converted to parallel with fork() - exec()
            int count = 0;
            int pid;
            auto c = container.begin();
            while (c != container.end())
            {
                pid = fork()
                if(pid == 0){
                    // execute each element in Container 
                    runnableObj.Run(*c++, workers[count++]);
                    return 0;
                }
                
                count %= workers.size();

            }
        }

        ActivationReturnType DeterministicClient::WaitForActivation() noexcept
        {
            // Blocks and returns with a process control value when the next activation is triggered by the Runtime
            ara::exec::ActivationReturnType state;
            
            read(fd, &state, sizeof(state));
            if(state == ActivationReturnType::kRun) DeterministicClient::Activated =  std::chrono::system_clock::now();
            return state;
        }
        uint64_t DeterministicClient::GetRandom() noexcept
        {
            return lrand48();
        }
        void DeterministicClient::SetRandomSeed(uint64_t seed) noexcept
        {
            srand48(seed);
        }

        DeterministicClient::TimeStamp DeterministicClient::GetActivationTime() noexcept
        {
            return Activated;
        }

        DeterministicClient::TimeStamp DeterministicClient::GetNextActivationTime() noexcept
        {
            
        }

    } // namespace exec

} // namespace ara
