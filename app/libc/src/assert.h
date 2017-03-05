#ifndef ASSERT_H_
#define ASSERT_H_
/**
 *  @file     assert.h
 *  @brief    Assertion macros.
 *  @author   Gerasimov A.S.
 *  @date     2014-10-14 15:40:48
 *  @note     Controlled by definitions from 'config.h'
 */
#include "config.h"
#include <stdbool.h>

#undef assert

#if CFG_ASSERTION == 1
#define assert(exp) do {\
    if( !(exp) ) {\
        __builtin_trap(); \
        while(true); \
    }\
} while (0)

#elif CFG_ASSERTION == 2
#define assert(exp) do {\
    if( !(exp) ) { \
        (void) fprintf(stderr, "\n\r" \
            "%s:%d: in '%s': assertion failed: %s", \
            __FILE__, __LINE__, __FUNCTION__, #exp); \
        for(;;);\
    }\
} while (0)

#else /* CFG_ASSERTION */
#define assert( exp )  ((void)0)
#endif

#endif  /*  ASSERT_H_  */
