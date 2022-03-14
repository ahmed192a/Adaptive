#ifndef ARA_SM_TRIGGER_INOUT_H
#define ARA_SM_TRIGGER_INOUT_H

#include "ara/sm/Trigger.hpp"
#include "ara/sm/Notifier.hpp"
//[SWS_SM_91009]
/******************************************************
 * Name : TriggerInOut_{StateGroup}
 * NameSpace : ara::sm
 *
 * Field : Notifier
 * Discribtion : State Management provides a service interface TriggerOut with a Notifier
 * HasGetter : True
 * HasNotifier : True
 * HasSetter : false
 *
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
        class TriggerInOut
        {
        private:
            Trigger<T> mTrigger;
            Notifier<T> mNotifier;

        public:
            TriggerInOut(T &state, TriggerHandler handler) : mTrigger(state, handler),
                                                             mNotifier(state)
            {
            }
            Trigger<T> &GetTrigger() noexcept
            {
                return mTrigger;
            }
            Notifier<T> &GetNotifier() noexcept
            {
                return mNotifier;
            }
        };
    }
}

#endif