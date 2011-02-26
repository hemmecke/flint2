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

void
_fmpz_poly_divrem(fmpz * Q, fmpz * R,
                  const fmpz * A, long lenA, const fmpz * B, long lenB)
{
    _fmpz_poly_divrem_divconquer(Q, R, A, lenA, B, lenB);
}

void
fmpz_poly_divrem(fmpz_poly_t Q, fmpz_poly_t R,
                 const fmpz_poly_t A, const fmpz_poly_t B)
{
    long lenA, lenB;
    fmpz_poly_t tQ, tR;
    fmpz *q, *r;

    lenA = A->length;
    lenB = B->length;

    if (lenB == 0)
    {
        printf("Exception: division by zero in fmpz_poly_divrem\n");
        abort();
    }

    if (lenA < lenB)
    {
        fmpz_poly_zero(Q);
        fmpz_poly_set(R, A);
        return;
    }

    if (Q == A || Q == B)
    {
        fmpz_poly_init2(tQ, lenA - lenB + 1);
        q = tQ->coeffs;
    }
    else
    {
        fmpz_poly_fit_length(Q, lenA - lenB + 1);
        q = Q->coeffs;
    }

    if (R == A || R == B)
    {
        fmpz_poly_init2(tR, lenA);
        r = tR->coeffs;
    }
    else
    {
        fmpz_poly_fit_length(R, lenA);
        r = R->coeffs;
    }

    _fmpz_poly_divrem(q, r, A->coeffs, lenA, B->coeffs, lenB);

    if (Q == A || Q == B)
    {
        _fmpz_poly_set_length(tQ, lenA - lenB + 1);
        fmpz_poly_swap(tQ, Q);
        fmpz_poly_clear(tQ);
    }
    else
        _fmpz_poly_set_length(Q, lenA - lenB + 1);

    if (R == A || R == B)
    {
        _fmpz_poly_set_length(tR, lenA);
        fmpz_poly_swap(tR, R);
        fmpz_poly_clear(tR);
    }
    else
        _fmpz_poly_set_length(R, lenA);

    _fmpz_poly_normalise(Q);
    _fmpz_poly_normalise(R);
}