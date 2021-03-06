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

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "nmod_vec.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;
    flint_randinit(state);

    printf("scalar_addmul_nmod....");
    fflush(stdout);

    /* Check (a + b*c) == a + (b*c) */
    for (i = 0; i < 10000; i++)
    {
        long len = n_randint(state, 100) + 1;
        mp_limb_t n = n_randtest_not_zero(state);
        mp_limb_t c = n_randint(state, n);
        nmod_t mod;

        mp_ptr vec = _nmod_vec_init(len);
        mp_ptr vec2 = _nmod_vec_init(len);
        mp_ptr vec3 = _nmod_vec_init(len);

        nmod_init(&mod, n);

        _nmod_vec_randtest(vec, state, len, mod);
        _nmod_vec_randtest(vec2, state, len, mod);
        mpn_copyi(vec3, vec2, len);

        _nmod_vec_scalar_mul_nmod(vec3, vec, len, c, mod);
        _nmod_vec_add(vec3, vec3, vec2, len, mod);

        _nmod_vec_scalar_addmul_nmod(vec2, vec, len, c, mod);

        result = _nmod_vec_equal(vec2, vec3, len);
        if (!_nmod_vec_equal(vec2, vec3, len))
        {
            printf("FAIL:\n");
            printf("len = %ld, n = %ld\n", len, n);
            abort();
        }

        _nmod_vec_free(vec);
        _nmod_vec_free(vec2);
        _nmod_vec_free(vec3);
    }

    flint_randclear(state);

    printf("PASS\n");
    return 0;
}
