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

#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

int fmpz_equal(const fmpz_t f, const fmpz_t g)
{
	if (f == g) return 1; // aliased inputs
	
	if (!COEFF_IS_MPZ(*f)) return (*f == *g); // if f is large it can't be equal to g
	else if (!COEFF_IS_MPZ(*g)) return 0; // f is large, so if g isn't....
	else return (mpz_cmp(COEFF_TO_PTR(*f), COEFF_TO_PTR(*g)) == 0); 
}