#ifndef MATH_H_
#define MATH_H_
/**
 *  @file    math.h
 *  @brief   Header file with math function.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
#define RANDOM_MAX  ((unsigned int)(-1))

/**
 *  Generate pseudo random number in range ( rand( ) >= min && rand() =< max ).
 */
#define random( _min, _max )\
	( ( rand() % (((ulong)(_max)) - ((ulong)(_min))) ) + ((ulong)(_min)) )

/**
 *  @brief
 *  Calculate percent (half) "p" of "n" (amount).
 *
 *  @example
 *  PERCENT( 4, 12 ); //return value 30 %
 */
#define PERCENT( p, n )\
	( ((p) * 100) / (n) )

/**
 *  Align up "v" up to divisible by "n".
 */ 
#define ALIGN_HI( v, n )\
({\
	typeof(v) _v;\
	\
	_v = ( (v) + (typeof(v))((n)-1) );\
	_v = ( _v / (typeof(v))(n) ) * (typeof(v))(n);\
	_v;\
})

/**
 *  Align like manner "ALIGN_HI" but divisible by 2.
 */
#define ALIGNe_HI( v, n )\
        ( (typeof(v))( ((ulong)(v) + ((n)-1)) & ~((n)-1) ) )

/**
 *  Align down "v" up to divisible by "n".
 */
#define ALIGN_LO( v, n )\
({\
	typeof(v) _v;\
	\
	_v = ( (v) / (typeof(v))(n) ) * (typeof(v))(n);\
	_v;\
})

/**
 *  Align like manner "ALIGNe_LO" but divisible by 2.
 */
#define ALIGNe_LO( v, n )\
	( (typeof(v))( (ulong)(v) & ~((n)-1) ) )


/**
 *  min()/max() macros that also do strict type-checking.
 *  See the "unnecessary" pointer comparison.
 */
#define min(x,y) ({		\
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x < _y ? _x : _y; })

#define max(x,y) ({		\
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x > _y ? _x : _y; })


#ifdef __cplusplus
extern "C" {
#endif

ulong  labs     ( long );
ulong  pow      ( ulong, ulong );
ulong  align_lo ( ulong, ulong );
ulong  align_hi ( ulong, ulong );
ulong  rand     ( void );
   int clz      ( uint32 );

   int divmnu ( unsigned short q[], unsigned short r[],
          const unsigned short u[],
          const unsigned short v[],
                int m, int n );

#define abs( i )\
	(uint)labs( (int)i )

#ifdef __cplusplus
}
#endif

#endif  /*  MATH_H_  */
