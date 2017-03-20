/**
 *  @file   WatchdogGroupInterface.cpp
 *  @brief  Watchdog common group interface.
 *  @author Gerasimov A.S.
 */
#include "dummy.h"
#include "watchdog/WatchdogGroupInterface.hpp"

namespace dev {

WatchdogGroupInterface::WatchdogGroupInterface ( void )
{
	virtual_disable = reinterpret_cast<WatchdogPrototype>(dummy_trap);
	virtual_enable  = reinterpret_cast<WatchdogPrototype>(dummy_trap);
	virtual_ack     = reinterpret_cast<WatchdogPrototype>(dummy_trap);
}


#if !defined(CXX_RTTI)
void WatchdogGroupInterface::disable ( void )
{
	virtual_disable( this );
}


void WatchdogGroupInterface::enable ( void )
{
	virtual_enable( this );
}


void WatchdogGroupInterface::ack ( void )
{
	virtual_ack( this );
}
#endif

}
