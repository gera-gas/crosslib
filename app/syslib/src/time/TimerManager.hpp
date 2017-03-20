#ifndef TIMER_MANAGER_HPP_
#define TIMER_MANAGER_HPP_
/**
 * @file   TimerManager.hpp
 * @author Gerasimov A.S.
 * @brief  Service to provides timer mechanisms.
 */
#include <stddef.h>
#include "config.h"
#include "typedef.h"

namespace time {

/**
 * @brief
 * Timer manager for control any timer object.
 * Object of this type should be called into interrupt timer handler.
 * Period of timer events usual is 1 millisecond.
 * @note
 * Need header: buffer/List.hpp
 */
class TimerManager
{
public:
	TimerManager( void );

#if defined(CXX_RTTI)
	virtual void enable   ( void )  = 0;
	virtual void disable  ( void )  = 0;
	virtual void interval ( ulong ) = 0;
#else
	void enable   ( void );
	void disable  ( void );
	void interval ( ulong );
#endif
	void add_timer ( Timer* );
	void del_timer ( Timer* );

	void start ( void );

protected:
#if !defined(CXX_RTTI)
	typedef void (*TimerManagerEnablePrototype)( void* );
	typedef void (*TimerManagerIntervalPrototype)( void*, ulong );

	TimerManagerEnablePrototype   virtual_enable;
	TimerManagerEnablePrototype   virtual_disable;
	TimerManagerIntervalPrototype virtual_interval;
#endif

private:
	buffer::List<Timer> timlist_;
};

} /* namespace time */

#endif /* TIMER_MANAGER_HPP_ */
