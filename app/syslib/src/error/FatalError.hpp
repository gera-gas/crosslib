#ifndef FATAL_ERROR_HPP_
#define FATAL_ERROR_HPP_
/**
 * @file     FatalError.hpp
 * @brief    Fatal error service mechanisms.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "config.h"
#include "typedef.h"
#include "dummy.h"

namespace error {

/**
 * Class describe global (fatal) errors descriptor.
 */
class FatalError {
public:

#if defined(CFG_ERROR_DETAILS)
	static char  *source_file;
	static char  *source_func;
	static size_t source_line;
#endif
	static int errorcode;

	/**
	 * Custom fatal error handler.
	 */
	static fptr_t handler;

	/**
	 * Fix error information and run error handler.
	 */
#if defined(CFG_ERROR_DETAILS)
	static void fix ( int errcode, const char *file, const char *func, size_t line );
#else
	static void fix ( int errcode );
#endif
};

} /* namespace error */

/**
 * Call fatal error handler.
 */
#if !defined(CFG_ERROR_DETAILS)
#define FATAL_ERROR( errcode )\
	error::FatalError::fix( errcode )
#else
#define FATAL_ERROR( errcode )\
	error::FatalError::fix( errcode, __FILE__, __FUNCTION__, __LINE__ )
#endif

#endif /* FATAL_ERROR_HPP_ */
