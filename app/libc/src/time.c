/**
 *  @file     time.c
 *  @brief    General standard functions.
 *  @author   Gerasimov A.S.
 *  @date     2013-07-29 15:40:50 +0400
 */
#include <stddef.h>
#include "time.h"

static clock_t halt ( void )
{
	while( 1 );
}

clockfunc_t clock = &halt;
