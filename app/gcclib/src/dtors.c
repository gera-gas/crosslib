/**
 *  @file     dtors.c
 *  @brief    Destructor organization for C++.
 *  @author   Gerasimov A.S.
 *  @date     2013-07-31 13:49:14 +0400
 *
 *  @details
 *  Example rules for linker script.
 *
.dtors : {
    __DTOR_LIST__ = .;
    ___DTORS_LIST___ = .;
    KEEP( *(.dtors.begin) )
    KEEP( *(.dtors) )
    KEEP( *(.dtors.end) )
    __DTOR_END__ = .;
    ___DTORS_END___ = .;
    } > <Your memory region>
 */
#include "typedef.h"

/**
 * Create frame to array with address of global destructors.
 */
static fptr_t dtors_list[1] __attribute__((section(".dtors.begin"), __used__)) = { (fptr_t) -1 };
static fptr_t dtors_end[1]  __attribute__((section(".dtors.end"),   __used__)) = { (fptr_t)  0 };

/**
 * Walk on "dtors_list" and call each global destructor.
 */
void __do_global_dtors_aux ( void )
{
	fptr_t  *fp;

	for( fp = dtors_list + 1; *fp != 0; fp++ )
		(**fp)( );
}
