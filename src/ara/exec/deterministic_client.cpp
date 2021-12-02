#include "deterministic_client.h"
#include "utility"
#include <vector>
namespace ara
{
    namespace exec
    {
        DeterministicClient::DeterministicClient()
        {
        }
        DeterministicClient::~DeterministicClient()
        {
        }


        template <typename ValueType, typename Container>
        void RunWorkerPool (WorkerRunnable< ValueType > &runnableObj, Container &container) noexcept{
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



        ara::core::Result<ActivationReturnType> WaitForActivation () noexcept{

        }
        uint64_t GetRandom()  noexcept{

        }
        void SetRandomSeed (uint64_t seed) noexcept{

        }

        ara::core::Result<DeterministicClient::TimeStamp> GetActivationTime () noexcept{

        }

        ara::core::Result<DeterministicClient::TimeStamp> GetNextActivationTime () noexcept{

        }


    } // namespace exec

} // namespace ara
