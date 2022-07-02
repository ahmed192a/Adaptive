/**
 * @file utility.hpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TIMER_UTILITY
#define __TIMER_UTILITY

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mytimer.hpp"
#include "callback.hpp"
#include <sys/wait.h>
#include <unistd.h>
#include <thread>
#include <chrono>
/**
 * @brief  This function is called by the timer. It's the handler for the timer.
 * 
 * @param timer_id 
 * @param user_data 
 */
void time_handler1(size_t timer_id, void *user_data)
{
    printf("Single shot timer expired.(%ld)\n", timer_id);
}
/**
 * @brief  This function is called by the timer. It's the handler for the timer.
 * 
 * @param timer_id 
 * @param user_data 
 */
void time_handler2(size_t timer_id, void *user_data)
{
    printf("2 s timer expired. (%ld)\n", timer_id);
}
/**
 * @brief  This function is called by the timer. It's the handler for the timer.
 * 
 * @param timer_id 
 * @param user_data 
 */
void time_handler3(size_t timer_id, void *user_data)
{
    printf("3 s timer expired. (%ld)\n", timer_id);
}
/**
 * @brief 
 * 
 */
class MyTimer : public Timer
{
    /**
     * @brief   The timer event runnable.
     * 
     */
    void timerEvent()
    {
        printf("3 s timer expired. \n");
    }
};
/**
 * @brief   
 * 
 */
class Callback1 : public TimerCallback::Runnable
{
    /**
     * @brief  The timer event runnable.
     * 
     */
    void run()
    {
        fprintf(stdout, "Callback1! \n");
        fflush(stdout);
    }
};
/**
 * @brief 
 * 
 */
class Callback2 : public TimerCallback::Runnable
{
    /**
     * @brief The timer event runnable.
     * 
     */
    void run()
    {
        fprintf(stdout, "Callback2! \n");
        fflush(stdout);
    }
};
#endif // __TIMER_UTILITY