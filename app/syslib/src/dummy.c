/**
 *  @file     dummy.c
 *  @brief    Dummy functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
int dummy_ret0 ( void )
{
	return 0;
}

int dummy_ret1 ( void )
{
	return 0;
}

void dummy_empty ( void )
{
	;
}

void dummy_loop ( void )
{
	while( 1 );
}

void dummy_trap ( void )
{
	__builtin_trap( );
}
