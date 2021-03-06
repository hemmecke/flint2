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

    Copyright (C) 2010 William Hart

******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <mpir.h>
#include "flint.h"
#include "nmod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i;
    flint_rand_t state;
    flint_randinit(state);

    printf("init/init2/realloc/clear....");
    fflush(stdout);

    for (i = 0; i < 10000; i++)
    {
        nmod_poly_t a;
        mp_limb_t n = n_randtest_not_zero(state);

        nmod_poly_init2(a, n, n_randint(state, 100));
        nmod_poly_clear(a);
    }

    for (i = 0; i < 10000; i++)
    {
        nmod_poly_t a;
        mp_limb_t n = n_randtest_not_zero(state);

        nmod_poly_init2(a, n, n_randint(state, 100));
        nmod_poly_realloc(a, n_randint(state, 100));
        nmod_poly_realloc(a, n_randint(state, 100));
        nmod_poly_clear(a);
    }

    for (i = 0; i < 10000; i++)
    {
        nmod_poly_t a;
        mp_limb_t n = n_randtest_not_zero(state);

        nmod_poly_init(a, n);
        nmod_poly_randtest(a, state, n_randint(state, 100));
        nmod_poly_clear(a);
    }

    flint_randclear(state);

    printf("PASS\n");
    return 0;
}
