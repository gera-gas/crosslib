/**
 * @file     FatalError.cpp
 * @brief    Fatal error service mechanisms.
 * @author   Gerasimov A.S.
 */
#include "error/FatalError.hpp"

namespace error {

#if defined(CFG_ERROR_DETAILS)
char  *FatalError::source_file = NULL;
char  *FatalError::source_func = NULL;
size_t FatalError::source_line = 0;
#endif
int FatalError::errorcode = 0;

/**
 * Custom fatal error handler.
 */
fptr_t FatalError::handler = dummy_loop;

/**
 * Fix error information and run error handler.
 */
#if defined(CFG_ERROR_DETAILS)
void FatalError::fix ( int errcode, char *file, char *func, size_t line )
#else
void FatalError::fix ( int errcode )
#endif
{
	errorcode = errcode;

#if defined(CFG_ERROR_DETAILS)
	source_file = file;
	source_func = func;
	source_line = line;
#endif

	handler( );
}

} /* namespace error */
