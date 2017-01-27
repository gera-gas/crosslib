/**
 * @file   main.c
 * @author Gerasimov A.S.
 * @brief  Using examples of library.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "typedef.h"
#include "multitask/thread.h"

/*
 * Example work of two PT object.
 */

/*
 * FOO PT object.
 */
clock_t goal;

PT_STATE( foo_state_0 )
{
	goal = 1000 + clock(); //delay 1000 ms

	return PT_NEXT;
}

PT_STATE( foo_state_1 )
{
	if( goal > clock() ) {
		return PT_HOLD;
	}

	printf( "FOO: working...\n");
	
	return PT_NEXT;
}

PT_CREATE( pt_foo, 0,
	foo_state_0,
	foo_state_1 );

/*
 * BAR PT object.
 */
PT_STATE( bar_state_0 )
{
	if( kbhit() ) {
		return PT_NEXT;
	}

	return PT_HOLD;
}

PT_STATE( bar_state_1 )
{
	char c = getchar();

	printf( "BAR: char=%c\n", c );

	if( c == 'q' ) exit(0);
	
	return PT_NEXT;
}

PT_CREATE( pt_bar, 0,
	bar_state_0,
	bar_state_1 );


int main ( void )
{
	printf( "*** Example work of two PT object ***\n");

	while( true ) {
		PT( pt_foo );
		PT( pt_bar );
	}

	return 0;
}
