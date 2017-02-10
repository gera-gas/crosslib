#ifndef GCC_LINKER_H_
#define GCC_LINKER_H_
/**
 *  @file     gcc_linker.h
 *  @brief    GCC helpers for linker script rules.
 *  @author   Gerasimov A.S.
 *  @date     2014-08-01 11:34:41
 */
#define LINK_CTORS( region )\
.ctors : {\
	__CTOR_LIST__ = .;\
	___CTORS_LIST___ = .;\
	KEEP( *(.ctors.begin) )\
	KEEP( *(.ctors) )\
	KEEP( *(.ctors.end) )\
	__CTOR_END__ = .;\
	___CTORS_END___ = .;\
} > region


#define LINK_DTORS( region )\
.dtors : {\
	__DTOR_LIST__ = .;\
	___DTORS_LIST___ = .;\
	KEEP( *(.dtors.begin) )\
	KEEP( *(.dtors) )\
	KEEP( *(.dtors.end) )\
	__DTOR_END__ = .;\
	___DTORS_END___ = .;\
} > region

#endif  /*  GCC_LINKER_H_  */
