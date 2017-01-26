/**
 * @file   main.c
 * @author Gerasimov A.S.
 * @brief  Using examples of library.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#include "typedef.h"
#include "multitask/thread.h"

PT_STATE( state_0 )
{
	printf( "State-0\n");

	return PT_NEXT;
}

PT_STATE( state_1 )
{
	printf( "State-1\n");
	
	return PT_NEXT;
}

PT_CREATE( pt_demo, false,
	state_0,
	state_1 );

int main ( void )
{
	printf( "Hello!!!\n");

	pt_start( &pt_demo, NULL, NULL );

	return 0;
}
