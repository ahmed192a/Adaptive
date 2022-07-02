/**
 * @file callback.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TIMER_CALLBACK
#define __TIMER_CALLBACK
#include <stdio.h>
#include "mytimer.hpp"
#include <unistd.h>

/**
 * @brief 
 * 
 */
class TimerCallback : public Timer
{
public:
    /**
     * @brief 
     * 
     */
    class Runnable
    {
    public:
        /**
         * @brief 
         * 
         */
        virtual void run() = 0;
    };
    /**
     * @brief 
     * 
     * @param h 
     */
    void registerEventRunnable(Runnable &h)
    {
        timerEventRunnable = &h;
    }
    /**
     * @brief 
     * 
     */
    void unregisterEventRunnable()
    {
        timerEventRunnable = NULL;
    }
    /**
     * @brief 
     * 
     */
    void timerEvent()
    {
        if (timerEventRunnable)
        {
            timerEventRunnable->run();
        }
    }

private:
    Runnable *timerEventRunnable = NULL;
};

#endif // __TIMER_CALLBACK