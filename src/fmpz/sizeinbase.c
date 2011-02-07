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
#include "ulong_extras.h"
#include "fmpz.h"

size_t fmpz_sizeinbase(const fmpz_t f, int b)
{
    size_t ans;
    fmpz d = *f;
    
    if (!COEFF_IS_MPZ(d))
    {
        mpz_t copy;
        mpz_init_set_si(copy, d);
        ans = mpz_sizeinbase(copy, b);
        mpz_clear(copy);
    }
    else
        ans = mpz_sizeinbase(COEFF_TO_PTR(d), b);
    return ans;
}

