/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/******************************************************************************

 Copyright (C) 2010 Fredrik Johansson

******************************************************************************/

#ifndef MPN_EXTRAS_H
#define MPN_EXTRAS_H

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"

/* Not defined in mpir.h */
mp_limb_t  __gmpn_modexact_1_odd(mp_srcptr src, mp_size_t size,
                                 mp_limb_t divisor);

#define mpn_modexact_1_odd __gmpn_modexact_1_odd

#define mpn_divisible_1_p(x, xsize, d) (mpn_modexact_1_odd(x, xsize, d) == 0)

static __inline__
int mpn_zero_p(mp_srcptr x, mp_size_t xsize)
{
    long i;
    for (i = 0; i < xsize; i++)
    {
        if (x[i])
            return 0;
    }
    return 1;
}

static __inline__
mp_size_t mpn_divexact_1(mp_ptr x, mp_size_t xsize, mp_limb_t d)
{
    mpn_divrem_1(x, 0, x, xsize, d);
    if (x[xsize - 1] == 0UL)
        xsize -= 1;
    return xsize;
}

void mpn_debug(mp_srcptr x, mp_size_t xsize);

mp_size_t mpn_remove_2exp(mp_ptr x, mp_size_t xsize, mp_bitcnt_t *bits);

mp_size_t mpn_remove_power_ascending(mp_ptr x, mp_size_t xsize,
                                     mp_ptr p, mp_size_t psize, ulong *exp);

int mpn_factor_trial(mp_srcptr x, mp_size_t xsize, long start, long stop);


/*
Macros for common operations with carry management.
Also automatically order the large operand first in mpn_mul
and mpn_add.
*/

#define MPN_SET(xx, xs, yy, ys)   \
do {                              \
    xs = ys;                      \
    mpn_copyi(xx, yy, ys);        \
} while (0)

#define CARRY(cy,xx,xs) if (cy) { xx[xs++] = cy; }

#define MPN_MUL_1(xx, xs, yy, ys, dd)           \
do {                                            \
    mp_limb_t __cy;                             \
    __cy = mpn_mul_1(xx, yy, ys, dd);           \
    xs = ys;                                    \
    CARRY(__cy, xx, xs);                        \
} while (0)

#define MPN_MUL(xx, xs, yy, ys, zz, zs)         \
do {                                            \
    mp_limb_t __top;                            \
    xs = ys + zs;                               \
    if (ys >= zs)                               \
        __top = mpn_mul(xx, yy, ys, zz, zs);    \
    else                                        \
        __top = mpn_mul(xx, zz, zs, yy, ys);    \
    if (!__top)                                 \
        xs--;                                   \
} while (0)

#define MPN_ADD(xx, xs, yy, ys, zz, zs)         \
do {                                            \
    mp_limb_t __cy;                             \
    if (ys >= zs)                               \
    {                                           \
        xs = ys;                                \
        __cy = mpn_add(xx, yy, ys, zz, zs);     \
    }                                           \
    else                                        \
    {                                           \
        xs = zs;                                \
        __cy = mpn_add(xx, zz, zs, yy, ys);     \
    }                                           \
    CARRY(__cy, xx, xs);                        \
} while (0)

/*
  Note: still assumes xs >= ys
*/
#define MPN_ADDMUL_1(xx, xs, yy, ys, dd)                     \
do {                                                         \
    mp_limb_t __cy;                                          \
    __cy = mpn_addmul_1(xx, yy, ys, dd);                     \
    if (__cy)                                                \
    {                                                        \
        if (xs == ys)                                        \
            xx[xs++] = __cy;                                 \
        else                                                 \
        {                                                    \
            __cy = mpn_add_1(xx+ys, xx+ys, xs-ys, __cy);     \
            CARRY(__cy, xx, xs);                             \
        }                                                    \
    }                                                        \
} while (0)



void
mpn_harmonic_odd_balanced(mp_ptr t, mp_size_t * tsize,
                          mp_ptr v, mp_size_t * vsize,
                          long a, long b, long n, int d);

#endif
