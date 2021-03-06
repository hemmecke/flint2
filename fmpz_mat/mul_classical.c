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

#include <stdlib.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mat.h"

void
fmpz_mat_mul_classical(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B)
{
    long ar, bc, br;
    long i, j, k;

    ar = A->r;
    br = B->r;
    bc = B->c;

    for (i = 0; i < ar; i++)
    {
        for (j = 0; j < bc; j++)
        {
            fmpz_zero(&C->rows[i][j]);

            for (k = 0; k < br; k++)
            {
                fmpz_addmul(&C->rows[i][j], &A->rows[i][k], &B->rows[k][j]);
            }
        }
    }
}
