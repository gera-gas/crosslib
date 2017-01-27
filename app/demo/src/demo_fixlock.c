/**
 * @file   main.c
 * @author Gerasimov A.S.
 * @brief  Example of fixlock mechanism.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "typedef.h"
#include "multitask/accessor.h"

struct sharedata_st {
	fixlock_t fixlock;
	char c;
};

struct sharedata_st sharedata = {
	/*
	 * fixlock init for two threads.
	 * begin state set for <getchar_thread>.
	 */
	{ .state = 0, .maxpos = 2 },
	/* clear char code. */
	.c = 0
};

#define FXLOCK_ID_THREAD_READ 0x0
#define FXLOCK_ID_THREAD_MAIN 0x1

/*
 * Read char thread.
 */
DWORD WINAPI getchar_thread ( LPVOID hDlg )
{
	char c;

	while( true )
	{
		/*
		 * Try catch shared resource for getchar thread.
		 */
		if( fixlock_try( &sharedata.fixlock, FXLOCK_ID_THREAD_READ ) )
		{
			printf( "Read thread, getchar: " );

			c = getchar();
			sharedata.c = c;
			/* Read char after 'Enter' */
			getchar();

			fixlock_free( &sharedata.fixlock );

			if( c == 'q' ) return 0;
		}
	}

	return 0;
}

/*
 * Main thread.
 */
int main ( void )
{
	char c;

	printf( "*** Example fixlock ***\n");

	DWORD dw_thread_id;
	HANDLE hthread = CreateThread( NULL, 0, getchar_thread, NULL, 0, &dw_thread_id );

	if( hthread == NULL ) {
	    printf( "ERROR: Unale to create thread.\n" );
	    return 1;
	}

	/*
	 * Work cycle of main thread.
	 */
	do {
		c = 0;
		/*
		 * Try catch shared resource for main thread.
		 */
		if( fixlock_try( &sharedata.fixlock, FXLOCK_ID_THREAD_MAIN ) )
		{
			c = sharedata.c;

			printf( "Main thread, putchar: %c\n", c );

			fixlock_free( &sharedata.fixlock );
		}
	} while( c != 'q' );

	CloseHandle( hthread );

	return 0;
}
