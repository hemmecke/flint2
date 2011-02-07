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
#include "fmpz_poly.h"
#include "fmpq_poly.h"

void
_fmpq_poly_evaluate_mpq(fmpz_t rnum, fmpz_t rden, 
                        const fmpz * poly, const fmpz_t den, long len, 
                        const fmpz_t anum, const fmpz_t aden)
{
    fmpz_t d;
    
    _fmpz_poly_evaluate_horner_mpq(rnum, rden, poly, len, anum, aden);
    fmpz_mul(rden, rden, den);
    
    fmpz_init(d);
    fmpz_gcd(d, rnum, rden);
    if (*d != 1L)
    {
        fmpz_divexact(rnum, rnum, d);
        fmpz_divexact(rden, rden, d);
    }
    fmpz_clear(d);
}

void 
fmpq_poly_evaluate_mpq(mpq_t res, const fmpq_poly_t poly, const mpq_t a)
{
    fmpz_t rnum, rden, anum, aden;
    fmpz_init(rnum);
    fmpz_init(rden);
    fmpz_init(anum);
    fmpz_init(aden);
    fmpz_set_mpz(anum, mpq_numref(a));
    fmpz_set_mpz(aden, mpq_denref(a));

    _fmpq_poly_evaluate_mpq(rnum, rden, poly->coeffs, poly->den, poly->length, anum, aden);

    fmpz_get_mpz(mpq_numref(res), rnum);
    fmpz_get_mpz(mpq_denref(res), rden);
    fmpz_clear(rnum);
    fmpz_clear(rden);
    fmpz_clear(anum);
    fmpz_clear(aden);
}
