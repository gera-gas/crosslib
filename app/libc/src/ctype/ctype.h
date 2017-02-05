#ifndef CTYPE_H_
#define CTYPE_H_
/**
 *  @file    ctype.h
 *  @brief   Macros to processing of standard C types.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */

/*
 * Macroses for ASCII string manipulation.
 */
#define ascii_todigit( c )  ( (c) - '0' )
#define ascii_tochar( n )   ( (char)((n) + '0') )
#define ascii_isdigit( c )  ( (unsigned)ascii_todigit(c) <= 9 )

#define isascii( c )  ( (c) <= 0x7F )
#define toascii( c )  ( (c)  & 0x7F )

#endif  /* CTYPE_H_ */
