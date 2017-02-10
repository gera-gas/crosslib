#ifndef ACCESSOR_H_
#define ACCESSOR_H_
/**
 *  @file    accessor.h
 *  @brief   Access control mechanism.
 *  @author  Gerasimov A.S.
 *  @date    2014-09-08 10:54:18
 */
#include <stdbool.h>
#include "typedef.h"

/**
 * @brief
 * Type with point to function guaranted of atom execution.
 * Implementation in <critical_section> object.
 */
typedef struct critical_section_st {
    fptr_t entry;
    fptr_t leave;
} critical_section_t;

/**
 * @brief
 * Type with create fixing limit synchronize object.
 * This is ordered orient mechanism, by also may be used fixlock_set.
 *
 * @details
 * Simple and fast non-blocking lock-free mechanism.
 * Fixlock it's a fixing limit objects for synchronize.
 * May be used for multi thread control and
 * CPUs interaction through shared memory.
 * 
 * @example
 *
 * FIXLOCK_CREATE( exlock, 2 );
 *
 * #define FXLOCK_ID_FOO 0x0
 * #define FXLOCK_ID_BAR 0x1
 *
 * void foo_thread ( void )
 * {
 *     if( fixlock_try(&exlock, FXLOCK_ID_FOO) ) {
 *         //TODO: your code
 *         fixlock_free( &exlock );
 *     }
 * }
 *
 * void bar_thread ( void )
 * {
 *     if( fixlock_try(&exlock, FXLOCK_ID_BAR) ) {
 *         //TODO: your code
 *         fixlock_free( &exlock );
 *     }
 * }
 */
typedef struct fixlock_st {
    uint state;
    uint maxpos;
    char data[0];
} fixlock_t;

#ifdef __cplusplus
extern "C" {
#endif

extern critical_section_t critical_section;

#ifdef __cplusplus
}
#endif

/**
 * Placed code into critical section.
 */
#define CRITICAL_SECTION( ... ) do {\
	critical_section.entry( );\
	__VA_ARGS__;\
	critical_section.leave( );\
} while( 0 )

/**
 * @def   FIXLOCK_CREATE
 * @brief Create fixlock object.
 *
 * @param name   : name of fixlock object.
 * @param maxpos : maximal clients number for this object.
 */
#define FIXLOCK_CREATE( name, maxpos )  fixlock_t name = { 0, maxpos }

/**
 * @def   FIXLOCK_TRY
 * @brief Try catch of fixlock object by ID.
 *
 * @param fixlock : [in] fixlock object address.
 * @param id      : [in] preset procedure ID.
 *
 * @retval true  : success catch.
 * @retval false : failed catch.
 */
#define FIXLOCK_TRY( fixlock, id )  ((fixlock)->state == id ? true : false)

/**
 * @def   FIXLOCK_FREE
 * @brief Free fixlock object for next owner.
 *
 * @param fixlock : [in] fixlock object address.
 */
#define FIXLOCK_FREE( fixlock ) do {\
	(fixlock)->state++;\
	if( (fixlock)->state >= (fixlock)->maxpos ) {\
		(fixlock)->state = 0;\
	}\
} while( 0 );

#endif  /*  ACCESSOR_H_  */
