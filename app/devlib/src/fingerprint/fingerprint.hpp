#ifndef FINGERPRINT_HPP_
#define FINGERPRINT_HPP_
/**
 * @file     fingerprint.hpp
 * @brief    Describe base API for fingerprint scanner devices.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "hal.hpp"
 */
#include <stddef.h>
#include "dummy.h"

namespace dev {

/**
 * API class for fingerprint scanner devices.
 */
class Fingerprint {
public:
	/**
	 * Contain specific error code.
	 */
	int errorcode;

	/**
	 * Fingerprint consctructor.
	 */
	Fingerprint ( sys::DevicePort *fp_port ) :
		errorcode(0),
		fp_port_(fp_port)
	{
		info_     = reinterpret_cast<bool (*)(void*, void*)>(dummy_loop);
		enroll_   = reinterpret_cast<int (*)(void*)>(dummy_loop);
		remove_   = reinterpret_cast<bool (*)(void*, int)>(dummy_loop);
		clear_    = reinterpret_cast<bool (*)(void*)>(dummy_loop);
		identify_ = reinterpret_cast<int (*)(void*)>(dummy_loop);
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
		return info_( this, outbuffer );
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
		return enroll_( this );
	}

	/**
	 * @brief
	 * Remove fingerprint from base.
	 *
	 * @param id : Page ID (Flash location of the template).
	 *
	 * @retval true  : success.
	 * @retval false : failed.
	 */
	bool remove ( int id )
	{
		return remove_( this );
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
		return clear_( this );
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
		return identify_( this );
	}

protected:
	/*
	 * Point to port device through device connected.
	 */
	sys::DevicePort *fp_port_;

	/*
	 * Overrided point to main API methods.
	 */
	bool (*info_)( void *, void * );
	int  (*enroll_)( void * );
	bool (*remove_)( void *, int );
	bool (*clear_)( void * );
	int  (*identify_)( void * );
};

} /* namespace dev */

#endif  /* FINGERPRINT_HPP_ */
