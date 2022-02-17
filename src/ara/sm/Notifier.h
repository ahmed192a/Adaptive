#ifndef ARA_SM_NOTIFIER_H
#define ARA_SM_NOTIFIER_H
#pragma once

#include <iostream>

#include <functional>

namespace ara
{
    namespace sm
    { 
        
        template <typename T1>
        using NotificationHandler = std::function<void(T1)>;
        template <typename T>
        class Notifier
        {
            private:
            T &mState;
            std::vector<NotificationHandler<T>> mSubsribers;

        public:
           
            Notifier(T &state) : mState{state}
            {
            }
            
           
            T Read() const noexcept
            {
                return mState;
            }

        };
    }
}

#endif