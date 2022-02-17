#ifndef ARA_SM_TRIGGER_H
#define ARA_SM_TRIGGER_H
#pragma once

#include <iostream>

#include <functional>

namespace ara
{
    namespace sm
    {
        using TriggerHandler = std::function<void()>;
        template <typename T>
        class Trigger
        {
        private:
            T &mState;
            TriggerHandler mHandler;

        public:
            Trigger(T &state, TriggerHandler handler) : mState{state},
                                                           mHandler{handler}
            {
            }

        void Write(T state)
            {
                if (mState != state)
                {
                    mState = state;
                    mHandler();
                }
            }
        };
    }
}

#endif