/**
 *  @file     md5.c
 *  @brief    MD5 hash algorythm implementaion.
 *  @author   Gerasimov A.S.
 *  @date     2015-11-06 13:42:34 +0400
 *  @note     Based on RSA Data Security, Inc. sources.
 * 
 *  MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
 *  MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
 *  MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
 *  MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
 *  MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
 *  MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") = d174ab98d277d9f5a5611c2c9f419d9f
 *  MD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890") = 57edf4a22be3c955ac49da2e2107b67a
 */
#include <stddef.h>
#include <stdbool.h>
#include "typedef.h"
#include "memory/memory.h"
#include "md5.h"

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * F, G, H and I it is base function MD5.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* 
 * ROTATE_LEFT left barrel shift x on n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* 
 * Преобразования FF, GG, HH и II для кругов 1, 2, 3, 4.
 * Циклический сдвиг отделен от добавления для предотвращения повторного расчета.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (uint32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (uint32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (uint32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (uint32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

/*
 * Кодирование входных данных (uint32) в выходные (uint8).
 * Предполагается, что размер кратен 4.
 */
static void encode( uint8 *output, uint32 *input, size_t len )
{
    uint32 i, j;

    for( i = 0, j = 0; j < len; i++, j += 4 )
    {
        output[j]   = (uint8)(input[i] & 0xff);
        output[j+1] = (uint8)((input[i] >> 8) & 0xff);
        output[j+2] = (uint8)((input[i] >> 16) & 0xff);
        output[j+3] = (uint8)((input[i] >> 24) & 0xff);
    }
}

/*
 * Декодирование входных данных (uint8) в выходные (uint32).
 * Предполагается, что размер кратен 4.
 */
static void decode( uint32 *output, uint8 *input, size_t len )
{
    uint32 i, j;

    for( i = 0, j = 0; j < len; i++, j += 4 )
    {
        output[i] = ((uint32)input[j]) | (((uint32)input[j+1]) << 8) |
                    (((uint32)input[j+2]) << 16) | (((uint32)input[j+3]) << 24);
    }
}


/*
 * Базовое преобразование MD5. Преобразует состояние поблочно.
 */
static void md5_transform( uint32 state[4], uint8 block[64] )
{
    uint32 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    decode( (uint32 *)x, block, 64 );

    /* Round 1 */
    FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

    /* Round 2 */
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

    /* Round 4 */
    II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    /* Обнуление чувствительных данных. */
    memset( x, 0, sizeof(x) );
}


/**
 * @brief
 * Выполняет инициалзацию контекста алгоритма.
 */
bool md5_init ( MD5_ctx *pctx )
{
    memset( pctx->buffer, 0, 64 );

    pctx->count[0] = pctx->count[1] = 0;

    pctx->state[0] = 0x67452301;
    pctx->state[1] = 0xefcdab89;
    pctx->state[2] = 0x98badcfe;
    pctx->state[3] = 0x10325476;

    return true;
}


/**
 * @brief
 * Процедура вычисления хэш.
 */
bool md5_update ( MD5_ctx *pctx, const void *data, size_t len )
{
    uint32  i;
    uint32  index;
    uint32  partlen;

    /*
     * Расчет числа байт mod 64.
     */
    index = (uint32)((pctx->count[0] >> 3) & 0x3F);

    pctx->count[0] += ((uint32)len << 3);
    /*
     * Обновление числа битов.
     */
    if( pctx->count[0] < ((uint32)len << 3) )
        pctx->count[1]++;

    pctx->count[1] += ((uint32)len >> 29);

    partlen = 64 - index;
    /*
     * Преобразование возможное число раз.
     */
    if( len >= partlen )
    {
        memcpy( &(pctx->buffer[index]), data, partlen );
        md5_transform( pctx->state, pctx->buffer );

        for( i = partlen; i + 63 < len; i += 64 )
        {
            md5_transform( pctx->state, (((uint8*)(data)) + i) );
        }

        index = 0;
    }
    else
        i = 0;

    /*
     * Буферизация оставшихся входных данных.
     */
    memcpy( &pctx->buffer[index], (const void *)(((uint8*)(data)) + i), len-i );

    return true;
}


/**
 * @brief
 * Процедура вычисления хэш.
 */
bool md5_final ( MD5_ctx *pctx, void *md )
{
    uint8 bits[8];
    uint32 index, padLen;

    /* Сохранение числа бит */
    encode( bits, pctx->count, 8 );

    /* Заполнение до 56 mod 64. */
    index  = (unsigned int)((pctx->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    md5_update( pctx, PADDING, padLen );

    /* Добавление размера (до заполнения) */
    md5_update( pctx, bits, 8 );

    /* Сохранение состояния в дайджесте */
    encode( md, pctx->state, 16 );

    /* Обнуление чувствительной информации. */
    memset( pctx, 0, sizeof(*pctx) );

    return true;
}
