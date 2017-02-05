/**
 *  @file     divmnu.c
 *  @brief    Divides huge unsigned values.
 *  @author   Purykin S.
 *  @date     2013-07-19 09:15:08 +0400
 */
#include <stddef.h>
#include "typedef.h"
#include "malloc/malloc.h"
#include "math/math.h"


/**
 * @brief Divides huge unsigned values.
 *
 * @param  q[] : The result of the division.
 * @param  r[] : The residual of the division.
 * @param  u[] : The dividend.
 * @param  v[] : The divisor.
 * @param  m   : An amount of signs of the divinend.
 * @param  n   : An amount of signs of the divisor.
 *
 * @retval If it has finished successful then returns 0, otherwise 1.
 *
 * @note 1) Used base number is 65536.
 *       2) u[0] and v[0] are least significant digits.
 *       3) m must be >= n.
 *       4) v[n-1] must not be equal 0.
 *       5) n must be > 0.
 */
int divmnu ( unsigned short q[], unsigned short r[],
       const unsigned short u[],
       const unsigned short v[],
             int m, int n )
{
    const uint32 b = 65536;	            /* Основание чисел (16 битов)	 */
    unsigned short *un, *vn;   	 		/* Нормализованный вид u и v	 */
    unsigned qhat;              		/* Предполагаемая цифра частного */
    unsigned rhat;              		/* Остаток			 */
    unsigned p;                 		/* Произведение двух цифр	 */
    int s, i, j, t, k;

    if (m < n || n <= 0 || v[n - 1] == 0)
        return 1;               		/* Возвращается при некорректном параметре */

    /*
     *  Частный случай делителя из одной цифры.  */
    if (n == 1) {
        k = 0;
        for (j = m - 1; j >= 0; j--) {
            q[j] = (k * b + u[j]) / v[0];
            k = (k * b + u[j]) - q[j] * v[0];
        }
        if (r != 0) r[0] = k;
        return 0;
    }

    /*
     *  Нормализация путем сдвига v влево, такого, что
     *  старший бит становится единичным, и сдвига и влево
     *  на ту же величину. Нам может потребоваться добавить
     *  старшую цифру к частному; мы делаем это безусловно
     */
    s = clz(v[n-1]) - 16;  /* 0 <= s <= 16 */
    vn = (unsigned short *)calloc(n,sizeof(short));
    for (i = n - 1; i > 0; i--)
        vn[i] = (v[i] << s) | (v[i-1] >> 16-s);
    vn[0] = v[0] << s;

    un = (unsigned short *)calloc((m + 1),sizeof(short));
    un[m] = u[m-1] >> 16-s;
    for (i = m - 1; i > 0; i--)
        un[i] = (u[i] << s) | (u[i-1] >> 16-s);
    un[0] = u[0] << s;

    for (j = m - n; j >= 0; j--) {
        /*
	 *  Вычисляем оценку q[j].  */
        qhat = (un[j+n]*b + un[j+n-1]) / vn[n-1];
        rhat = (un[j+n]*b + un[j+n-1]) - qhat*vn[n-1];
again:
        if (qhat >= b || qhat*vn[n-2] > b*rhat + un[j+n-2]) {
            qhat = qhat - 1;
            rhat = rhat + vn[n-1];
            if (rhat < b) goto again;
        }
        /*
	 *  Умножение и вычитание.  */
        k = 0;
        for (i = 0; i < n; i++) {
            p = qhat * vn[i];
            t = un[i+j] - k - (p & 0xFFFF);
            un[i+j] = t;
            k = (p >> 16) - (t >> 16);
        }
        t = un[j+n] - k;
        un[j+n] = t;
	/*
	 *  Сохранение цифры частного.  */
        q[j] = qhat;
	/*
	 *  Если мы вычли слишком много,
	 *  вернем назад.
	 */
        if (t < 0) 				
        { 					
            q[j] = q[j] - 1;
            k = 0;
            for (i = 0; i < n; i++) {
                t = un[i+j] + vn[i] + k;
                un[i+j] = t;
                k = t >> 16;
            }
            un[j+n] = un[j+n] + k;
        }
    }

    /*
     * Если вызывающей функции нужно значение остатка,
     * денормализуем и возвращаем его.
     */
    if (r != 0)
    {
        for (i = 0; i < n; i++)
            r[i] = (un[i] >> s) | (un[i+1] << 16-s);
    }

    free(un);
    free(vn);

    return 0;
}
