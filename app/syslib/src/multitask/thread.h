#ifndef THREAD_H_
#define THREAD_H_
/**
 *  @file     thread.h
 *  @brief    Thread export mechanism.
 *  @author   Gerasimov A.S.
 *  @date     2014-09-08 10:54:18
 */
#include <stddef.h>
#include <stdbool.h>
#include "typedef.h"

typedef uint ( *ptfunc_t )( const void *, void * );
typedef uint ptlock_t;

/**
 * @enum   pt_result_t
 * @brief  Return types of PT process.
 */
typedef enum {
	PT_FLAG_STEPMODE = 0x1,  /** PT do one function in step only  */
	PT_FLAG_SHARED   = 0x2   /** Use critical section for lock PT */
} ptflag_t;

/**
 * @enum   pt_result_t
 * @brief  Return types of PT.
 */
typedef enum {
	PT_STATE_ATWORK, /** PT walk in state functions.             */
	PT_STATE_FINISH  /** PT went all functions or will be reset. */
} pt_result_t;

/**
 * @struct  pt_t
 * @brief   Structure with main contex of PT object.
 */
typedef struct pt_st {
        char  *name;
    ptflag_t   flags;
      size_t   numb;
    ptlock_t   owner;
    ptfunc_t  *init;
    ptfunc_t  *state;
} pt_t;

/*
 * Possible values returned by state function.
 */
#define PT_HOLD      (uint)(0)               /** Hold in current state.       */
#define PT_NEXT      (uint)(1)               /** Go to next state of process. */
#define PT_BACK      (uint)(-1)              /** Back to previous state.      */
#define PT_JUMP( i ) (uint)(i)               /** Jump to any state.           */
#define PT_RESET     (uint)((uint)(-1) / 2)  /** Complete process forcibly.   */

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
 *
 *  @param  name  : name of PT object;
 *  @param  flags : see to ptflag_t;
 *  @param  ...   : state handler functions.
 */
#define PT_CREATE( name, flags, ... )\
	ptfunc_t __##name[] = { __VA_ARGS__, NULL };\
	pt_t name = { #name, flags, (sizeof(__##name)/sizeof(__##name[0])) - 1, PTLOCK_FREE, &__##name[0], &__##name[0] };

/**
 * Starting PT process without arguments.
 */
#define PT( pt ) pt_start( &pt, NULL, NULL )

#ifdef __cplusplus
extern "C" {
#endif

pt_result_t pt_start  ( pt_t *pt, const void *argin, void *argout );
       bool pt_lock   ( pt_t *pt, ptlock_t owner );
       void pt_unlock ( pt_t *pt );

#ifdef __cplusplus
}
#endif

#define PTLOCK_FREE  ((uint)(-1))
#define PTLOCK_OWNER ((uint)__builtin_return_address( 0 ))

#endif  /*  THREAD_H_  */