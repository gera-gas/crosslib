#ifndef STDLIB_H_
#define STDLIB_H_
/**
 *  @file     stdlib.h
 *  @brief    General standard functions.
 *  @author   Gerasimov A.S.
 *  @date     2013-07-29 15:40:50 +0400
 */
#ifdef __cplusplus
extern "C" {
#endif

void *bsearch ( const void *,
                const void *,
                size_t, size_t,
                int (*compar)(const void *, const void *) );

#ifdef __cplusplus
}
#endif

#endif  /*  STDLIB_H_  */
