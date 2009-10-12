/*============================================================================

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

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int result;
   printf("factor_trial_partial....");
   fflush(stdout);
 
   for (ulong i = 0; i < 10000UL; i++) /* Test random numbers */
   {
      mp_limb_t n1, n2, prod, limit;
      n_factor_t factors;

      n_factor_init(&factors);

      n1 = n_randtest_not_zero();
      limit = n_sqrt(n1);
      n2 = n_factor_trial_partial(&factors, n1, &prod, 10000UL, limit);
      
      if (n1 != n2*prod)
      {
         printf("FAIL\n");
         printf("n1 = %lu, n2 = %lu, prod = %lu\n", n1, n2, prod);
         abort();
      }

      for (ulong i = 0; i < factors.num; i++)
      {
         n2 *= n_pow(factors.p[i], factors.exp[i]);
      }

      result = (n1 == n2);

      if (!result)
      {
         printf("FAIL\n");
         printf("n1 = %lu, n2 = %lu\n", n1, n2); 
         abort();
      }
   }
   
   printf("PASS\n");
   return 0;
}
