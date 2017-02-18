#ifndef GMACRO_H_
#define GMACRO_H_
/**
 *  @file    gmacro.h
 *  @brief   General Macros.
 *  @author  Gasimov A.S.
 *  @date    2013-02-22 19:02:04 +0400
 */
#include "typedef.h"

/**
 *  @def  SWAP16( v )
 *  @brief
 *  «агружает 2 байта из адреса 'v' с переворотом.
 */
#define SWAP16( v )\
	( (pvUINT8(v+1) << 8) | pvUINT8(v) )

/**
 *  @def SWAP32( v )
 *  @brief
 *  «агружает 4 байта из адреса 'v' с переворотом.
 */
#define SWAP32( v )\
	( (pvUINT8((v)+3) << 24) | (pvUINT8((v)+2) << 16) | (pvUINT8((v)+1) << 8) | pvUINT8(v) )

/**
 *  @def LOAD32( v )
 *  @brief
 *  «агружает 4 байта из адреса 'v'.
 */
#define LOAD32( v )\
	( (pvUINT8(v) << 24) | (pvUINT8((v)+1) << 16) | (pvUINT8((v)+2) << 8) | pvUINT8((v)+3) )

/**
 *  @def LOAD16( v )
 *  @brief
 *  «агружает 2 байта из адреса 'v'.
 */
#define LOAD16( v )\
	( (pvUINT8((v)) << 8) | pvUINT8((v)+1) )

/**
 *  @def MAKESTR( left, right )
 *  @brief
 *  —оединение выражени€ 'left' и 'right' в одну строку.
 */
#define MAKESTR( left, right )\
	left##right

/**
 *  @def TOSTR( str )
 *  @brief
 *  ѕреобразование константы 'str' в строку
 */
#define  TOSTR( str )  _TOSTR( str )
#define _TOSTR( str )  #str

/**
 *  @def SHIFT_L( v, s )
 *  @brief
 *  ÷иклический сдвиг влево.
 *
 *  @param v [in] : сдвигаемое значение.
 *  @param s [in] : количество разр€дов дл€ сдвига.
 */
#define SHIFT_L( v, s )\
	( ((v) << s) | ((v) >> (sizeof(v) * 8) - (s)) )

/**
 *  @def SHIFT_R( v, s )
 *  @brief
 *  ÷иклический сдвиг вправо.
 *
 *  @param v [in] : сдвигаемое значение.
 *  @param s [in] : количество разр€дов дл€ сдвига.
 */
#define SHIFT_R( v, s )\
	( ((v) >> s) | ((v) << (sizeof(v) * 8) - (s)) )


/*  ____________________________________________________________________________
 *
 *  ћакросы обращени€ к €чейке пам€ти
 *  через указатель типа.
 *  ____________________________________________________________________________
 */
#define pTYPE( t, v )\
	(*(t*)(v))

#ifdef __cplusplus
#define TOCAST( t, v )\
	reinterpret_cast<t*>(v)
#endif

#define pUINT8(p)    (*(uint8 *)(p))
#define pINT8(p)     (*(int8 *)(p))
#define pvUINT8(p)   (*(volatile uint8 *)(p))
#define pvINT8(p)    (*(volatile int8 *)(p))

#define pUINT16(p)   (*(uint16 *)(p))
#define pINT16(p)    (*(int16 *)(p))
#define pvUINT16(p)  (*(volatile uint16 *)(p))
#define pvINT16(p)   (*(volatile int16 *)(p))

#define pUINT32(p)   (*(uint32 *)(p))
#define pINT32(p)    (*(int32 *)(p))
#define pvUINT32(p)  (*(volatile uint32 *)(p))
#define pvINT32(p)   (*(volatile int32 *)(p))

#define pUINT64(p)   (*(uint64 *)(p))
#define pINT64(p)    (*(int64 *)(p))
#define pvUINT64(p)  (*(volatile uint64 *)(p))
#define pvINT64(p)   (*(volatile int64 *)(p))


/*  ____________________________________________________________________________
 *
 *  ¬ыделение старшей/младшей части
 *  из указанного типа данных.
 *  ____________________________________________________________________________
 */
#define LPART8( w )\
	(((uint8)(w)) & 0xF)
#define HPART8( w )\
	((((uint8)(w)) >> 4) & 0xF)

#define LPART16( w )\
	(((uint16)(w)) & 0xFF)
#define HPART16( w )\
	((((uint16)(w)) >> 8) & 0xFF)

#define LPART32( w )\
	(((uint32)(w)) & 0xFFFF)
#define HPART32( w )\
	((((uint32)(w)) >> 16) & 0xFFFF)

#define LPART64( w )\
	(((uint64)(w)) & 0xFFFFFFFF)
#define HPART64( w )\
	((((uint64)(w)) >> 32) & 0xFFFFFFFF)


/*  ____________________________________________________________________________
 *
 *  ћакрос подсчитывает кол-во единичных бит в 32-х разр€дном слове,
 *  переданного в качестве параметра "v32" и возвращает вычисленное значение.
 *  
 *  "Hacker's Delight": by Henry S. Warren, Jr.
 *  ____________________________________________________________________________
 */
#define CALC_BITS32( v32 )\
({\
	uint32 ret;\
	\
	ret = (v32);\
	/* посчет кол-ва единичных бит */\
	ret = (ret & 0x55555555) + ((ret >>  1) & 0x55555555);\
	ret = (ret & 0x33333333) + ((ret >>  2) & 0x33333333);\
	ret = (ret & 0x0F0F0F0F) + ((ret >>  4) & 0x0F0F0F0F);\
	ret = (ret & 0x00FF00FF) + ((ret >>  8) & 0x00FF00FF);\
	ret = (ret & 0x0000FFFF) + ((ret >> 16) & 0x0000FFFF);\
	\
	ret;\
})


/*  ____________________________________________________________________________
 *
 *  Convert 'n' to bytes numbers.
 *
 *  SIZE_BIT -- bit to bytes.
 *  SIZE_KB  -- Kbytes to bytes.
 *  SIZE_MB  -- Mbytes to bytes.
 *  SIZE_GB  -- Gbytes to bytes.
 *  ____________________________________________________________________________
 */
#define SIZE_BIT( n )\
	((n)/8)

#define SIZE_KB( n )\
	((n) * 1024)

#define SIZE_MB( n )\
	((n) * 1024 * 1024)

#define SIZE_GB( n )\
	((n) * 1024 * 1024 * 1024)

/*
 *  ¬ычисл€ет количество элементов массива.  */
#define ARRAY_SIZE( m )\
	sizeof(m)/sizeof(m[0])

#if !defined(offsetof)
/*
 * Calculate unit offset of struct. */
#define offsetof( type, ident )\
	((size_t) (size_t) &((type *)0)->ident)

#endif /* !defined(offsetof) */

#endif  /*  GMACRO_H_  */
