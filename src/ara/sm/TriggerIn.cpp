#include "./TriggerIn.h"

namespace ara
{
    namespace sm
    {
       template <typename T>
       TriggerIn::TriggerIn(T &state, TriggerHandler handler) : mTrigger(state, handler)
       {}
       Trigger<T> &GetTrigger() noexcept
       {
                return mTrigger;
       }
        
    }
}
