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
#include "fmpq_poly.h"

void fmpq_poly_scalar_div_mpz(fmpq_poly_t rop, const fmpq_poly_t op, const mpz_t c)
{
    fmpz_t fc;
    
    if (mpz_sgn(c) == 0)
    {
        printf("Exception: division by zero in fmpq_poly_scalar_div_mpz\n");
        abort();
    }
    
    fmpz_init(fc);
    fmpz_set_mpz(fc, c);
    fmpq_poly_scalar_div_fmpz(rop, op, fc);
    fmpz_clear(fc);
}

