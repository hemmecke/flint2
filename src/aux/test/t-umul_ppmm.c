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
#include "ulong_extras.h"

int main(void)
{
   int i, j, result;
   flint_rand_t state;
   flint_randinit(state);

   printf("umul_ppmm....");
   fflush(stdout);

   for (i = 0; i < 1000000; i++)
   {
      mp_limb_t ph1, pl1, ph2, pl2, pl2old, m1, m2, bit;

      m1 = n_randtest(state);
      m2 = n_randtest(state);
      
      umul_ppmm(ph1, pl1, m1, m2);
      
      pl2old = 0UL;
      pl2 = 0UL;
      ph2 = 0UL;
      bit = 1UL;
      for (j = 0; j < FLINT_BITS; j++)
      {
         if (m2 & bit)
         {
            pl2 += (m1 << j);
            ph2 += (pl2 < pl2old);
            ph2 += r_shift(m1, FLINT_BITS - j);
            pl2old = pl2;
         }
         bit <<= 1;
      }

      result = ((ph2 == ph1) && (pl2 == pl1));

      if (!result)
      {
         printf("FAIL:\n");
         printf("m1 = %lu, m2 = %lu\n", m1, m2); 
         printf("ph2 = %lu, ph1 = %lu, pl2 = %lu, pl1 = %lu\n", ph2, ph1, pl2, pl1);
         abort();
      }
   }

   flint_randclear(state);

   printf("PASS\n");
   return 0;
}
