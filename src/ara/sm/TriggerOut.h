#ifndef ARA_SM_TRIGGER_OUT_H
#define ARA_SM_TRIGGER_OUT_H

#include "./Notifier.h"

//[SWS_SM_91008]
/******************************************************
 * Name : TriggerOut_{StateGroup}
 * NameSpace : ara::sm
 * Field : Notifier
 * Discribtion : State Management provides a service interface TriggerOut with a Notifier
 * HasGetter : True
 * HasNotifier : True
 * HasSetter : false
 *******************************************************/

namespace ara
{
    namespace sm
    {
        template <typename T>
        class TriggerOut
        {
        private:
            Notifier<T> mNotifier;

        public:
            explicit TriggerOut (T &state) : mNotifier(state)
        {}
        Notifier<T> &GetNotifier() noexcept
        {
           return mNotifier;
        }
        };
    }
}

#endif