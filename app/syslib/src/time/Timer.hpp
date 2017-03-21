#ifndef TIMER_HPP_
#define TIMER_HPP_
/**
 * @file   Timer.hpp
 * @author Gerasimov A.S.
 * @brief  Service to provides timer mechanisms.
 */
#include <stddef.h>
#include "typedef.h"

namespace time {

/**
 * Timer class.
 * This objects will be handling into TimerManager.
 */
class Timer
{
public:
	LIST_ITEM( Timer );

	ulong tick;
	bool autoreload;
	fptr_t function;

	/**
	 * @brief
	 * Timer constructor.
	 *
	 * @param value_tick       : [in] execution interval in TimerManager ticks.
	 * @param value_autoreload : [in] after elapse time automatically run timer again.
	 * @param value_function   : [in] after elapse time this function will be running.
	 *
	 * @note
	 * TimerManager ticks -- time period running of TimeManager object.
	 * TimerManager ticks custom defined into each software project.
	 */
	Timer ( ulong value_tick, bool value_autoreload = false, fptr_t value_function = NULL );

	void reload ( void ) {
		tick = tick_initial_;
	}

	/**
	 * @brief
	 * Timer manager for control any timer object.
	 * Object of this type should be called into interrupt timer handler.
	 * Period of timer events usual is 1 millisecond.
	 * @note
	 * Need header: buffer/List.hpp
	 */
	class Manager
	{
	public:
		Manager( void );

	#if defined(CXX_RTTI)
		virtual void enable   ( void )  = 0;
		virtual void disable  ( void )  = 0;
		virtual void interval ( ulong ) = 0;

		virtual void timer_add    ( Timer* );
		virtual void timer_delete ( Timer* );
	#else
		void enable   ( void );
		void disable  ( void );
		void interval ( ulong );

		void timer_add    ( Timer* );
		void timer_delete ( Timer* );
	#endif
		void start ( void );

	protected:
	#if !defined(CXX_RTTI)
		typedef void (*EnablePrototype)( void* );
		typedef void (*IntervalPrototype)( void*, ulong );
		typedef void (*AddPrototype)( void*, Timer* );

		EnablePrototype   virtual_enable;
		EnablePrototype   virtual_disable;
		IntervalPrototype virtual_interval;
		AddPrototype      virtual_add;
		AddPrototype      virtual_delete;
	#endif

	private:
		buffer::List<Timer> timlist_;
	};

	/**
	 * Global timer manager pointer.
	 * Should be defined into hardware layer initialization.
	 */
	static Manager *manager;

private:
	ulong tick_initial_;
};

} /* namespace time */

#endif /* TIMER_HPP_ */
