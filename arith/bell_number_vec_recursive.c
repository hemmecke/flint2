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

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <math.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "arith.h"

void _bell_number_vec_recursive(fmpz * b, long n)
{
    long i, k;
    fmpz * t;

    if (n <= SMALL_BELL_LIMIT)
    {
        for (i = 0; i < n; i++)
            fmpz_set_ui(b + i, bell_number_small[i]);
        return;
    }

    n -= 1;
    t = _fmpz_vec_init(n);

    fmpz_set_ui(t, 1UL);
    fmpz_set_ui(b, 1UL);
    fmpz_set_ui(b + 1, 1UL);

    for (i = 1; i < n; i++)
    {
        fmpz_set(t + i, t);
        for (k = i; k > 0; k--)
            fmpz_add(t + k - 1, t + k - 1, t + k);
        fmpz_set(b + i + 1, t);
    }

    _fmpz_vec_clear(t, n);
}
