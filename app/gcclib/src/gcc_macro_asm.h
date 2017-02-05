#ifndef CC_ASM_H_
#define CC_ASM_H_
/**
 *  @file     cc_asm.h
 *  @brief    GCC assembler macros.
 *  @author   Gerasimov A.S.
 *  @date     2013-06-24
 */
#ifdef __ASM__


/**
 *  @brief  Macros to definition for assembler macros.
 *  @param  name : [in] name of definition macros.
 *  @param  ...  : [in] arguments of macros.
 *  @note   Pair macroses, BEGINM - start definition,
 *          ENDM - end definition.
 */
#define BEGINM( name, ... )\
	.macro name __VA_ARGS__

#define ENDM( )\
	.endm


/**
 *  @brief  Macros to definition global symbols.
 *  @param  mark : [in] name of mark.
 */
#define GLOBAL( mark )\
	.global mark;\
	mark:

/**
 *  @brief  Macros to definition local symbols.
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
 *  @brief  Macros to definition for assembler function name.
 *  @param  name : [in] name function.
 *  @note   Pair macroses, BEGINF - start definition,
 *          ENDF - end definition.
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
#endif  /*  CC_ASM_H_  */
