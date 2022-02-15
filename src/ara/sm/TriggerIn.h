#ifndef ARA_SM_TRIGGER_IN_H
#define ARA_SM_TRIGGER_IN_H

#include "./Trigger.h"

//[SWS_SM_91007]

/******************************************************
 * Name : TriggerIn_{StateGroup}
 * NameSpace : ara::sm
 * Field : Trigger
 * Discribtion :  each Adaptive Application can influence the behavior of 
 * State Management by writing to the Trigger fields provided
 * (as part of the serviceinterface TriggerIn) by State Management
 * Type : Using Templats To provides it.
 * HasGetter : false
 * HasNotifier : false
 * HasSetter : true
 *******************************************************/

namespace ara
{
    namespace sm
    {
        template <typename T>
        class TriggerIn
        {
        private:
            Trigger<T> mTrigger;

        public:
           
       TriggerIn(T &state, TriggerHandler handler) : mTrigger(state, handler)
       {}
       Trigger<T> &GetTrigger() noexcept
       {
                return mTrigger;
       }

        };
    }
}

#endif