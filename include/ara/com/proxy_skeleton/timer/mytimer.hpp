/**
 * @file mytimer.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CPP_TIMER_H_
#define __CPP_TIMER_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

/** CLOCKID*/
#define CLOCKID CLOCK_MONOTONIC

/** Enumeration of CppTimer types */
enum timerType_t
{
    PERIODIC,
    ONESHOT
};

/**
 * @brief Timer class which repeatedly fires. It's wrapper around the
 *        POSIX per-process timer. 
 * 
 */
class Timer
{

public:
    /**
     * @brief Construct a new Timer object
     * 
     * @param signo The signal used by the timer.
     */
    Timer(const int signo = SIGRTMIN)
    {
        /* We create a static handler catches the signal SIG */
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = handler;
        sigemptyset(&sa.sa_mask);
        if (sigaction(signo, &sa, NULL) == -1)
            throw("Could not create signal handler");

        /* Create the timer */
        sev.sigev_notify = SIGEV_SIGNAL;
        sev.sigev_signo = signo;
        /* Cruical is that the signal carries the pointer to this class instance here
         because the handler just handles anything that comes in! */
        sev.sigev_value.sival_ptr = this;
        // create the timer
        if (timer_create(CLOCKID, &sev, &timerid) == -1)
            throw("Could not create timer");
    }

    /**
     * Starts the timer. The timer fires first after
     * the specified time in nanoseconds and then at
     * that interval in PERIODIC mode. In ONESHOT mode
     * the timer fires once after the specified time in
     * nanoseconds.
     * @param nanosecs Time in nanoseconds
     * @param type Either PERIODIC or ONESHOT
     **/
    void startns(long nanosecs, timerType_t type = PERIODIC);

    /**
     * Starts the timer. The timer fires first after
     * the specified time in milliseconds and then at
     * that interval in PERIODIC mode. In ONESHOT mode
     * the timer fires once after the specified time in
     * milliseconds.
     * @param millisecs Time in milliseconds
     * @param type Either PERIODIC or ONESHOT
     **/
    void startms(long millisecs, timerType_t type = PERIODIC);

    /**
     * @brief Stops the timer by disarming it. It can be re-started
     * with start().
     **/
    void stop();

    /**
     * @brief Destructor disarms the timer, deletes it and
     * disconnect the signal handler.
     **/
    ~Timer();

protected:
    /**
     * @brief Abstract function which needs to be implemented by the children.
     * This is called every time the timer fires.
     **/
    virtual void timerEvent() = 0;

private:
    timer_t timerid = 0;
    struct sigevent sev;
    struct sigaction sa;
    struct itimerspec its;

    inline static void handler(int, siginfo_t *si, void *)
    {
        (reinterpret_cast<Timer *>(si->si_value.sival_ptr))->timerEvent();
    }
};

#endif // __CPP_TIMER_H_
