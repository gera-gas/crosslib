#ifndef ACCESSOR_H_
#define ACCESSOR_H_
/**
 *  @file    accessor.h
 *  @brief   Access control mechanism.
 *  @author  Gerasimov A.S.
 *  @date    2014-09-08 10:54:18
 */
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

typedef struct PresetLock__st {
    uint8 i;
    fptr_t leave;
} preset_lock_t;


#ifdef __cplusplus
extern "C" {
#endif

extern critical_section_t critical_section;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Placed code into critical section.
 */
#define CRITICAL_SECTION( ... ) do {\
	critical_section.entry( );\
	__VA_ARGS__;\
	critical_section.leave( );\
} while( 0 )

#endif  /*  ACCESSOR_H_  */
