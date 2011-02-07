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

#include "flint.h"
#include "ulong_extras.h"
#include "nmod_mat.h"
#include "nmod_vec.h"


/*
  Standard Fisher-Yates shuffle to randomise an array; returns whether
  the permutation is even (0) or odd (1)
*/
static int shuffle(long * array, flint_rand_t state, long n)
{
    long i, j, tmp;
    int parity;

    parity = 0;
    for (i = n - 1; i > 0; i--)
    {
        j = n_randint(state, i+1);
        parity ^= (i == j);
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
    return parity;
}

int
nmod_mat_randpermdiag(nmod_mat_t mat, flint_rand_t state, 
                      const mp_limb_t * diag, long n)
{
    int parity;
    long i;
    long * rows;
    long * cols;

    rows = malloc(sizeof(long) * mat->r);
    cols = malloc(sizeof(long) * mat->c);

    for (i = 0; i < mat->r; i++) rows[i] = i;
    for (i = 0; i < mat->c; i++) cols[i] = i;

    parity = shuffle(rows, state, mat->r);
    parity ^= shuffle(cols, state, mat->c);

    _nmod_vec_zero(mat->entries, mat->r * mat->c);

    for (i = 0; i < n; i++)
        mat->rows[rows[i]][cols[i]] = diag[i];

    free(rows);
    free(cols);

    return parity;
}
