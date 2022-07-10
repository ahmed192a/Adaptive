/**
 * @file mytimer.cpp
 * @author 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../../../../../include/ara/com/proxy_skeleton/timer/mytimer.hpp"

/**
 * @brief 
 * 
 * @param nanosecs 
 * @param type 
 */

void Timer::startns(long nanosecs, timerType_t type)
{
	switch (type)
	{
	case (PERIODIC):
		/* starts after specified period of nanoseconds */
		its.it_value.tv_sec = nanosecs / 1000000000;
		its.it_value.tv_nsec = nanosecs % 1000000000;
		its.it_interval.tv_sec = nanosecs / 1000000000;
		its.it_interval.tv_nsec = nanosecs % 1000000000;
		break;
	case (ONESHOT):
		/* fires once after specified period of nanoseconds */
		its.it_value.tv_sec = nanosecs / 1000000000;
		its.it_value.tv_nsec = nanosecs % 1000000000;
		its.it_interval.tv_sec = 0;
		its.it_interval.tv_nsec = 0;
		break;
	}
	if (timer_settime(timerid, 0, &its, NULL) == -1)
		throw("Could not start timer");
}

/**
 * @brief 
 * 
 * @param millisecs 
 * @param type 
 */
void Timer::startms(long millisecs, timerType_t type)
{
	switch (type)
	{
	case (PERIODIC):
		/* starts after specified period of milliseconds */
		its.it_value.tv_sec = millisecs / 1000;
		its.it_value.tv_nsec = (millisecs % 1000) * 1000000;
		its.it_interval.tv_sec = millisecs / 1000;
		its.it_interval.tv_nsec = (millisecs % 1000) * 1000000;
		break;
	case (ONESHOT):
		/* fires once after specified period of milliseconds */
		its.it_value.tv_sec = millisecs / 1000;
		its.it_value.tv_nsec = (millisecs % 1000) * 1000000;
		its.it_interval.tv_sec = 0;
		its.it_interval.tv_nsec = 0;
		break;
	}
	if (timer_settime(timerid, 0, &its, NULL) == -1)
		throw("Could not start timer");
}
/**
 * @brief 
 * 
 */
void Timer::stop()
{
	struct itimerspec itsnew;
	itsnew.it_value.tv_sec = 0;
	itsnew.it_value.tv_nsec = 0;
	itsnew.it_interval.tv_sec = 0;
	itsnew.it_interval.tv_nsec = 0;
	timer_settime(timerid, 0, &itsnew, &its);
}
/**
 * @brief Destroy the Cpp Timer:: Cpp Timer object
 * 
 */
Timer::~Timer()
{
	stop();
	/* delete the timer */
	timer_delete(timerid);
	/* default action for signal handling */
	signal(sev.sigev_signo, SIG_IGN);
}