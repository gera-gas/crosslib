#ifndef WATCHDOG_GROUP_INTERFACE_HPP_
#define WATCHDOG_GROUP_INTERFACE_HPP_
/**
 *  @file   WatchdogGroupInterface.hpp
 *  @brief  Watchdog common group interface.
 *  @author Gerasimov A.S.
 */
namespace dev {

class WatchdogGroupInterface {
public:
	WatchdogGroupInterface ( void );

#if defined(CXX_RTTI)
	virtual void disable ( void ) = 0;
	virtual void enable  ( void ) = 0;
	virtual void ack     ( void ) = 0;
#else
	void disable ( void );
	void enable  ( void );
	void ack     ( void );
#endif
protected:
#if !defined(CXX_RTTI)
	typedef void (*WatchdogPrototype)(void*);

	WatchdogPrototype virtual_disable;
	WatchdogPrototype virtual_enable;
	WatchdogPrototype virtual_ack;
#endif
};

}

#endif  /*  WATCHDOG_GROUP_INTERFACE_HPP_  */
