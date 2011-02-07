/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 Fredrik Johansson

******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "arith.h"
#include "mpn_extras.h"
#include "ulong_extras.h"


void fmpz_factor(fmpz_factor_t factor, const fmpz_t n)
{
    ulong exp;
    mp_limb_t p;
    mpz_t x;
    mp_ptr xd;
    mp_size_t xsize;
    long found;
    long trial_start, trial_stop;

    if (!COEFF_IS_MPZ(*n))
    {
        _fmpz_factor_si(factor, *n);
        return;
    }

    _fmpz_factor_set_length(factor, 0);

    /* Make an mpz_t copy whose limbs will be mutated */
    mpz_init(x);
    fmpz_get_mpz(x, n);
    if (x->_mp_size < 0)
    {
        x->_mp_size = -(x->_mp_size);
        factor->sign = -1;
    }
    else
    {
        factor->sign = 1;
    }

    xd = x->_mp_d;
    xsize = x->_mp_size;

    /* Factor out powers of two */
    xsize = mpn_remove_2exp(xd, xsize, &exp);
    if (exp)
    {
        _fmpz_factor_append_ui(factor, 2UL, exp);
    }

    trial_start = 1;
    trial_stop = 1000;
    while (xsize > 1)
    {
        found = mpn_factor_trial(xd, xsize, trial_start, trial_stop);

        if (found)
        {
            p = flint_primes[found];
            exp = 1;
            xsize = mpn_divexact_1(xd, xsize, p);

            /* Check if p^2 divides n */
            if (mpn_divisible_1_p(xd, xsize, p))
            {
                /* TODO: when searching for squarefree numbers
                   (Moebius function, etc), we can abort here. */
                xsize = mpn_divexact_1(xd, xsize, p);
                exp = 2;
            }

            /* If we're up to cubes, then maybe there are higher powers */
            if (exp == 2 && mpn_divisible_1_p(xd, xsize, p))
            {
                xsize = mpn_divexact_1(xd, xsize, p);
                xsize = mpn_remove_power_ascending(xd, xsize, &p, 1, &exp);
                exp += 3;
            }

            _fmpz_factor_append_ui(factor, flint_primes[found], exp);
            /* printf("added %lu %lu\n", flint_primes[found], exp); */

            /* Continue using only trial division as long as it is successful.
               This allows quickly factoring huge highly composite numbers
               such as factorials, which can arise in some applications. */
            trial_start = found + 1;
            trial_stop = trial_start + 1000;
            continue;
        }
        else
        {
            /* Insert primality test, perfect power test, other factoring
               algorithms here... */
            trial_start = trial_stop;
            trial_stop = trial_start + 1000;
        }
    }

    /* Any single-limb factor left? */
    if (xd[0] != 1)
    {
        _fmpz_factor_extend_factor_n(factor, xd[0]);
    }

    mpz_clear(x);
    return;
}
