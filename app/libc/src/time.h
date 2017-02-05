#ifndef TIME_H_
#define TIME_H_
/**
 *  @file     time.h
 *  @brief    General standard functions.
 *  @author   Gerasimov A.S.
 *  @date     2013-07-29 15:40:50 +0400
 */
#include <stddef.h>

typedef size_t clock_t;
typedef clock_t (*clockfunc_t)( void );

#ifdef __cplusplus
extern "C" {
#endif

extern clockfunc_t clock;

#ifdef __cplusplus
}
#endif

#endif  /*  TIME_H_  */
