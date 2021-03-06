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

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "nmod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result = 1;
    flint_rand_t state;
    flint_randinit(state);
    
    printf("compose_divconquer....");
    fflush(stdout);

    /* Compare aliasing */
    for (i = 0; i < 5000; i++)
    {
        nmod_poly_t a, b, r1;
        mp_limb_t n = n_randtest_not_zero(state);
        
        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(r1, n);
        nmod_poly_randtest(a, state, n_randint(state, 30));
        nmod_poly_randtest(b, state, n_randint(state, 15));
        
        nmod_poly_compose_divconquer(r1, a, b);
        nmod_poly_compose_divconquer(a, a, b);
        
        result = nmod_poly_equal(r1, a);
        if (!result)
        {
            printf("FAIL:\n");
            printf("a->length = %ld, n = %lu\n", a->length, a->mod.n);
            nmod_poly_print(r1), printf("\n\n");
            nmod_poly_print(a), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(r1);
    }
    
    /* Compare other aliasing */
    for (i = 0; i < 5000; i++)
    {
        nmod_poly_t a, b, r1;
        mp_limb_t n = n_randtest_not_zero(state);
        
        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(r1, n);
        nmod_poly_randtest(a, state, n_randint(state, 30));
        nmod_poly_randtest(b, state, n_randint(state, 15));
        
        nmod_poly_compose_divconquer(r1, a, b);
        nmod_poly_compose_divconquer(b, a, b);
        
        result = nmod_poly_equal(r1, b);
        if (!result)
        {
            printf("FAIL:\n");
            printf("a->length = %ld, n = %lu\n", a->length, a->mod.n);
            nmod_poly_print(r1), printf("\n\n");
            nmod_poly_print(b), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(r1);
    }
    
    /* Compare with compose_horner */
    for (i = 0; i < 5000; i++)
    {
        nmod_poly_t a, b, r1, r2;
        mp_limb_t n = n_randtest_not_zero(state);
        
        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(r1, n);
        nmod_poly_init(r2, n);
        nmod_poly_randtest(a, state, n_randint(state, 30));
        nmod_poly_randtest(b, state, n_randint(state, 15));
        
        nmod_poly_compose_divconquer(r1, a, b);
        nmod_poly_compose_horner(r2, a, b);
        
        result = nmod_poly_equal(r1, r2);
        if (!result)
        {
            printf("FAIL:\n");
            printf("a->length = %ld, n = %lu\n", a->length, a->mod.n);
            nmod_poly_print(r1), printf("\n\n");
            nmod_poly_print(r2), printf("\n\n");
            abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(r1);
        nmod_poly_clear(r2);
    }
    
    flint_randclear(state);

    printf("PASS\n");
    return 0;
}
