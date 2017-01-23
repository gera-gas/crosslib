#ifndef PSEUDO_THREAD_H_
#define PSEUDO_THREAD_H_
/**
 *  @file     smm.h
 *  @brief    Pseudo thread export mechanism.
 *  @author   Gerasimov A.S.
 *  @date     2014-09-08 10:54:18
 */
#include "typedef.h"

typedef  uint ( *ptfunc_t )( const void *, void * );

/**
 * @enum   pt_result_t
 * @brief  Return types of PT process.
 */
typedef enum {
	PT_STATE_ATWORK,
	PT_STATE_FINISH
} pt_result_t;

/**
 * @struct  pt_t
 * @brief   Structure with main contex of PT process.
 */
typedef struct {
        char  *name;
        uint   stepmode;
        uint   numb;
        uint   lock;
    ptfunc_t  *init;
    ptfunc_t  *state;
} pt_t;


/*
 * Possible values returned by state.
 */
#define PT_HOLD       (uint)(0)                /** Hold in current state.      */
#define PT_NEXT       (uint)(1)                /** Go to next stateof process. */
#define PT_BACK       (uint)(-1)               /** Back to previous state.     */
#define PT_JUMP( i )  (uint)(i)                /** Jump to any state.          */
#define PT_RESET      (uint)((uint)(-1) / 2)   /** Complete process forcibly.  */

/**
 *  @def    PT_STATE
 *  @brief  Create a function protoype for state handler.
 *  @param  n : function name.
 */
#define PT_STATE( name )\
	uint name ( const void *argin, void *argout )

/**
 *  @def    PT_CREATE
 *  @brief  Create PT object.
 *  @param  name : name of PT object;
 *  @param  step : true(1) stepmode on or false(0) to stepmode off;
 *  @param  ...  : state handler functions.
 */
#define PT_CREATE( name, step, ... )\
	ptfunc_t __##name[] = { __VA_ARGS__, NULL };\
	pt_t name = { #name, step, (sizeof(__##name)/sizeof(__##name[0])) - 1, 0, &__##name[0], &__##name[0] };

/**
 * Starting PT process without arguments.
 */
#define PT( pt ) pt_start( &pt, NULL, NULL )

#ifdef __cplusplus
extern "C" {
#endif

pt_result_t pt_start ( pt_t *smm, const void *argin, void *argout );

#ifdef __cplusplus
}
#endif

#endif  /*  PSEUDO_THREAD_H_  */
