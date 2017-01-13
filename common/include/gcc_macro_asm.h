#ifndef _CC_ASM_H
#define _CC_ASM_H
/**
 *  @file     cc_asm.h
 *  @brief    GCC assembler macros.
 *  @author   Gerasimov A.S.
 *  @date     2013-06-24
 */
#ifdef __ASM__


/**
 *  @brief  Macros to defenition for assembler macros.
 *  @param  name : [in] name of defenition macros.
 *  @param  ...  : [in] arguments of macros.
 *  @note   Pair macroses, BEGINM - start defenition,
 *          ENDM - end defenition.
 */
#define BEGINM( name, ... )\
	.macro name __VA_ARGS__

#define ENDM( )\
	.endm


/**
 *  @brief  Macros to defenition global symbols.
 *  @param  mark : [in] name of mark.
 */
#define GLOBAL( mark )\
	.global mark;\
	mark:

/**
 *  @brief  Macros to defenition local symbols.
 *  @param  mark : [in] name of mark.
 */
#define LOCAL( mark )\
	mark:


/**
 *  @brief  Create array, element type (long,etc ... ) = type,
 *          and element numbers = num.
 *  @param  name  : [in] name of array.
 *  @param  type  : [in] type of array (element size).
 *  @param  num   : [in] numbers array elements (array size).
 *  @param  value : [in] initialize value.
 *  @note   if 'value' not defined then init-value set to zero.
 */
#define VARIABLE( name, type, num, ... )\
	_VARIABLE  name, type, num, __VA_ARGS__

.macro _VARIABLE  name, type, num, value=0
	.global \name
	\name:
	.rep \num
		\type \value
	.endr
.endm


/**
 *  @brief  Create ascii string sized by zero.
 *  @param  name  : [in] name string.
 *  @param  str   : [in] string value.
 */
#define STRING( name, str )\
	GLOBAL( name );\
	.ascii str;\
	.byte 0


/**
 *  @brief  Macros to defenition for assembler function name.
 *  @param  name : [in] name function.
 *  @note   Pair macroses, BEGINF - start defenition,
 *          ENDF - end defenition.
 */
#define BEGINF( name )\
	_BEGINF  name

#define ENDF( name )\
	_ENDF  name

.macro _BEGINF  name
	.global \name
	\name:
.endm

.macro _ENDF  name
	e_\name:
/*	.size name,e_\name-name  */
.endm


/**
 *  @brief  Repeat assembler line.
 *  @param  num  : [in] numbers of repeat.
 *  @param  ...  : [in] line to repeat.
 *  @note
 *
 *  Example      :  LINE_REPEATE( 2, nop )
 *  Converted to :  nop
 *                  nop
 */
#define LINE_REPEAT( num, ... )\
	.rep num;\
		__VA_ARGS__;\
	.endr
 
#endif  /*  __ASM__  */
#endif  /*  _CC_ASM_H  */
