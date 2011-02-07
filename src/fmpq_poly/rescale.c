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
#include "fmpq_poly.h"

/*
    Sets {res, denr, len} to {poly, den, len} with the indeterminate rescaled 
    by the rational {xnum, xden}.
    
    Assumes len > 0 and {xnum, xden} is non-zero and in lowest terms.
    
    ( a0 + a1 t + ... + an t^n ) / d

    Replace t by xnum t / xden
    
    (a0 + a1 xnum t / xden + ... + an xnum^n t^n / xden^n) / d
    ( a0 xden^n + a xnum xden^{n-1} t + ... + an xnum^n t^n ) / (d xden^n)
    
*/

void
_fmpq_poly_rescale(fmpz * res, fmpz_t denr, const fmpz * poly, 
              const fmpz_t den, long len, const fmpz_t xnum, const fmpz_t xden)
{
    if (len < 2L)
    {
        if (res != poly)
        {
            _fmpz_vec_set(res, poly, len);
            fmpz_set(denr, den);
        }
    }
    else
    {
        long i;
        fmpz_t t;
        
        fmpz_init(t);
        
        fmpz_set_ui(t, 1UL);
        fmpz_set(res, poly);
        for (i = 1L; i < len; i++)
        {
            fmpz_mul(t, t, xnum);
            fmpz_mul(res + i, poly + i, t);
        }
        fmpz_set_ui(t, 1UL);
        for (i = len - 2L; i >= 0L; i--)
        {
            fmpz_mul(t, t, xden);
            fmpz_mul(res + i, res + i, t);
        }
        fmpz_mul(denr, den, t);
        
        fmpz_clear(t);
        
        _fmpq_poly_canonicalise(res, denr, len);
    }
}

void fmpq_poly_rescale(fmpq_poly_t res, const fmpq_poly_t poly, const mpq_t x)
{
    fmpz_t xnum, xden;
    
    if (mpq_sgn(x) == 0)
    {
        fmpq_poly_zero(res);
        return;
    }
    if (poly->length < 2L)
    {
        fmpq_poly_set(res, poly);
        return;
    }
    
    fmpz_init(xnum);
    fmpz_init(xden);
    fmpz_set_mpz(xnum, mpq_numref(x));
    fmpz_set_mpz(xden, mpq_denref(x));
    
    fmpq_poly_fit_length(res, poly->length);
    _fmpq_poly_rescale(res->coeffs, res->den, 
                       poly->coeffs, poly->den, poly->length, xnum, xden);
    _fmpq_poly_set_length(res, poly->length);
    
    fmpz_clear(xnum);
    fmpz_clear(xden);
}
