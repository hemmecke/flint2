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

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpz_poly.h"

void
_fmpz_poly_resultant(fmpz_t res, const fmpz * poly1, long len1, 
                                 const fmpz * poly2, long len2)
{
    if (len2 == 1)
    {
        fmpz_pow_ui(res, poly2, len1 - 1);
    }
    else
    {
        fmpz_t a, b, g, h, t;
        fmpz *A, *B, *W;
        const long alloc = len1 + len2;
        long sgn = 1;

        fmpz_init(a);
        fmpz_init(b);
        fmpz_init(g);
        fmpz_init(h);
        fmpz_init(t);

        A = W = _fmpz_vec_init(alloc);
        B = W + len1;

        _fmpz_poly_content(a, poly1, len1);
        _fmpz_poly_content(b, poly2, len2);
        _fmpz_vec_scalar_divexact_fmpz(A, poly1, len1, a);
        _fmpz_vec_scalar_divexact_fmpz(B, poly2, len2, b);

        fmpz_set_ui(g, 1);
        fmpz_set_ui(h, 1);

        fmpz_pow_ui(a, a, len2 - 1);
        fmpz_pow_ui(b, b, len1 - 1);
        fmpz_mul(t, a, b);

        do
        {
            const long d = len1 - len2;

            if (!(len1 & 1L) & !(len2 & 1L))
                sgn = -sgn;

            _fmpz_poly_pseudo_rem_cohen(A, A, len1, B, len2);

            for (len1--; len1 >= 0 && !A[len1]; len1--) ;
            len1++;

            if (len1 == 0)
            {
                fmpz_zero(res);
                goto cleanup;
            }

            {
                fmpz * T;
                long len;
                T = A, A = B, B = T;
                len = len1, len1 = len2, len2 = len;
            }

            fmpz_pow_ui(a, h, d);
            fmpz_mul(b, g, a);
            _fmpz_vec_scalar_divexact_fmpz(B, B, len2, b);

            fmpz_pow_ui(g, A + (len1 - 1), d);
            fmpz_mul(b, h, g);
            fmpz_divexact(h, b, a);
            fmpz_set(g, A + (len1 - 1));

        } while (len2 > 1);

        fmpz_pow_ui(g, h, len1 - 1);
        fmpz_pow_ui(b, B + (len2 - 1), len1 - 1);
        fmpz_mul(a, h, b);
        fmpz_divexact(h, a, g);

        fmpz_mul(res, t, h);
        if (sgn < 0)
            fmpz_neg(res, res);

      cleanup:

        fmpz_clear(a);
        fmpz_clear(b);
        fmpz_clear(g);
        fmpz_clear(h);
        fmpz_clear(t);

        _fmpz_vec_clear(W, alloc);
    }
}

void
fmpz_poly_resultant(fmpz_t res, const fmpz_poly_t poly1, 
                                const fmpz_poly_t poly2)
{
    const long len1 = poly1->length, len2 = poly2->length;

    if (len1 == 0 || len2 == 0)
    {
        fmpz_zero(res);
        return;
    }

    if (len1 >= len2)
        _fmpz_poly_resultant(res, poly1->coeffs, len1, poly2->coeffs, len2);
    else
    {
        _fmpz_poly_resultant(res, poly2->coeffs, len2, poly1->coeffs, len1);
        if ((len1 > 1) && (!(len1 & 1L) & !(len2 & 1L)))
            fmpz_neg(res, res);
    }
}
