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

    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpz_poly.h"

#define FLINT_INV_NEWTON_CUTOFF  32

void 
_fmpz_poly_inv_series_newton(fmpz * Qinv, const fmpz * Q, long n)
{
    if (n == 1)
    {
        fmpz_set_ui(Qinv, 1);
    }
    else
    {
        const long alloc = FLINT_MAX(2 * n, 3 * FLINT_INV_NEWTON_CUTOFF);
        long *a, i;
        fmpz *W;

        W = _fmpz_vec_init(alloc);

        for (i = 1; (1L << i) < n; i++) ;

        a = (long *) malloc(i * sizeof(long));
        a[i = 0] = n;
        while (n >= FLINT_INV_NEWTON_CUTOFF)
            a[++i] = (n = (n + 1) / 2);

        /* Base case */
        {
            fmpz *Qrev = W + 2 * FLINT_INV_NEWTON_CUTOFF;

            _fmpz_poly_reverse(Qrev, Q, n, n);
            _fmpz_vec_zero(W, 2*n - 2);
            fmpz_set_ui(W + (2*n - 2), 1);
            _fmpz_poly_div_basecase(Qinv, W, W, 2*n - 1, Qrev, n);
            _fmpz_poly_reverse(Qinv, Qinv, n, n);
        }
        
        for (i--; i >= 0; i--)
        {
            n = a[i];

            _fmpz_poly_mullow(W, Q, n, Qinv, n, n);
            fmpz_sub_ui(W, W, 1);
            _fmpz_poly_mullow(W + n, W, n, Qinv, n, n);
            _fmpz_vec_sub(Qinv, Qinv, W + n, n);
        }

        _fmpz_vec_clear(W, alloc);
        free(a);
    }
}

void fmpz_poly_inv_series_newton(fmpz_poly_t Qinv, const fmpz_poly_t Q, long n)
{
    fmpz *Qcopy;
    int Qalloc;

    if (Q->length >= n)
    {
        Qcopy = Q->coeffs;
        Qalloc = 0;
    }
    else
    {
        long i;
        Qcopy = (fmpz *) malloc(n * sizeof(fmpz));
        for (i = 0; i < Q->length; i++)
            Qcopy[i] = Q->coeffs[i];
        for ( ; i < n; i++)
            Qcopy[i] = 0;
        Qalloc = 1;
    }

    if (Qinv != Q)
    {
        fmpz_poly_fit_length(Qinv, n);
        _fmpz_poly_inv_series_newton(Qinv->coeffs, Qcopy, n);
    }
    else
    {
        fmpz_poly_t t;
        fmpz_poly_init2(t, n);
        _fmpz_poly_inv_series_newton(t->coeffs, Qcopy, n);
        fmpz_poly_swap(Qinv, t);
        fmpz_poly_clear(t);
    }
    
    _fmpz_poly_set_length(Qinv, n);
    _fmpz_poly_normalise(Qinv);

    if (Qalloc)
        free(Qcopy);
}

