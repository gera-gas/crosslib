#ifndef FINGERPRINT_HPP_
#define FINGERPRINT_HPP_
/**
 * @file     fingerprint.hpp
 * @brief    Describe base API for fingerprint scanner devices.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "hal/Port.hpp"
 * #include "hal/Device.hpp"
 */
#include <stddef.h>
#include "dummy.h"

namespace dev {

/**
 * API class for fingerprint scanner devices.
 */
class Fingerprint : public hal::Device {
public:
	/**
	 * Fingerprint consctructor.
	 */
	Fingerprint ( hal::Port *fp_port ) :
		Device(fp_port)
	{
		virtual_info     = reinterpret_cast<bool (*)(void*, void*)>(dummy_loop);
		virtual_enroll   = reinterpret_cast<int (*)(void*)>(dummy_loop);
		virtual_remove   = reinterpret_cast<bool (*)(void*, int)>(dummy_loop);
		virtual_clear    = reinterpret_cast<bool (*)(void*)>(dummy_loop);
		virtual_identify = reinterpret_cast<int (*)(void*)>(dummy_loop);
	}

	/**
	 * @brief
	 * Get device information.
	 *
	 * @param outbuffer : [out] buffer address for store information.
	 *
	 * @retval true  : success.
	 * @retval false : failed.
	 */
	bool info ( void *outbuffer )
	{
		return virtual_info( this, outbuffer );
	}

	/**
	 * @brief
	 * Enroll new fingerprint.
	 *
	 * @retval >=0 : Page ID (Flash location of the template).
	 * @retval  <0 : failed.
	 */
	int enroll ( void )
	{
		return virtual_enroll( this );
	}

	/**
	 * @brief
	 * Remove fingerprint from base.
	 *
	 * @param pageid : Page ID (Flash location of the template).
	 *
	 * @retval true  : success.
	 * @retval false : failed.
	 */
	bool remove ( int pageid )
	{
		return virtual_remove( this, pageid );
	}

	/**
	 * @brief
	 * Clear device (Remove all fingerprints from base).
	 *
	 * @retval true  : success.
	 * @retval false : failed.
	 */
	bool clear ( void )
	{
		return virtual_clear( this );
	}

	/**
	 * @brief
	 * Identify fingerprint.
	 *
	 * @retval >=0 : Page ID (Flash location of the template).
	 * @retval  <0 : failed.
	 */
	int identify ( void )
	{
		return virtual_identify( this );
	}

protected:
	/*
	 * Overrided point to main API methods.
	 */
	bool (*virtual_info)( void *, void * );
	int  (*virtual_enroll)( void * );
	bool (*virtual_remove)( void *, int );
	bool (*virtual_clear)( void * );
	int  (*virtual_identify)( void * );
};

} /* namespace dev */

#endif  /* FINGERPRINT_HPP_ */
