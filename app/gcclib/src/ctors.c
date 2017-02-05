/**
 *  @file     ctors.c
 *  @brief    Constructor organization for C++.
 *  @author   Gerasimov A.S.
 *  @date     2013-07-31 13:49:11 +0400
 *
 *  @details
 *  Example rules for linker script.
 *
 *  .ctors : {
 *    KEEP( *(.ctors.begin) )
 *    KEEP( *(.ctors) )
 *    KEEP( *(.ctors.end) )
 *  } > <Your memory region>
 */
#include "typedef.h"

/**
 * Create frame to array with address of global constructors.
 */
static fptr_t ctors_list[1] __attribute__((section(".ctors.begin"), __used__)) = { (fptr_t) -1 };
static fptr_t ctors_end[1]  __attribute__((section(".ctors.end"),   __used__)) = { (fptr_t)  0 };

/**
 * Walk on "ctors_list" and call each global contructor.
 */
void __do_global_ctors_aux ( void )
{
	fptr_t  *fp;

	for( fp = ctors_list + 1; *fp != 0; fp++ )
		(**fp)( );
}
