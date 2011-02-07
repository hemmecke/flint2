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
    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#ifndef FMPZ_VEC_H
#define FMPZ_VEC_H

#include <mpir.h>
#include "fmpz.h"

/*  Memory management  *******************************************************/

fmpz * _fmpz_vec_init(long len);

void _fmpz_vec_clear(fmpz * vec, long len);

/*  Randomisation  ***********************************************************/

void _fmpz_vec_randtest(fmpz * f, flint_rand_t state, 
                        long len, mp_bitcnt_t bits);

void _fmpz_vec_randtest_unsigned(fmpz * f, flint_rand_t state, 
                                 long len, mp_bitcnt_t bits);

/*  Bit sizes  ***************************************************************/

long _fmpz_vec_max_bits(const fmpz * vec, long len);

mp_size_t _fmpz_vec_max_limbs(const fmpz * vec, long len);

/*  Input and output  ********************************************************/

int _fmpz_vec_fprint(FILE * file, const fmpz * vec, long len);

static __inline__
int _fmpz_vec_print(const fmpz * vec, long len)
{
    return _fmpz_vec_fprint(stdout, vec, len);
}

int _fmpz_vec_fread(FILE * file, fmpz ** vec, long * len);

static __inline__
int _fmpz_vec_read(fmpz ** vec, long * len)
{
    return _fmpz_vec_fread(stdin, vec, len);
}

/*  Assignment and basic manipulation  ***************************************/

void _fmpz_vec_set(fmpz * vec1, const fmpz * vec2, long len2);

void _fmpz_vec_swap(fmpz * vec1, fmpz * vec2, long len2);

void _fmpz_vec_zero(fmpz * vec, long len);

void _fmpz_vec_neg(fmpz * vec1, const fmpz * vec2, long len2);

/*  Comparison  **************************************************************/

int _fmpz_vec_equal(const fmpz * vec1, const fmpz * vec2, long len);

int _fmpz_vec_is_zero(const fmpz * vec, long len);

/* Sorting  ******************************************************************/

void _fmpz_vec_sort(fmpz * vec, long len);

/*  Addition  ****************************************************************/

void _fmpz_vec_add(fmpz * res, const fmpz * vec1, 
                                               const fmpz * vec2, long len2);

void _fmpz_vec_sub(fmpz * res, const fmpz * vec1, 
                                               const fmpz * vec2, long len2);

/*  Scalar multiplication and division  **************************************/

void _fmpz_vec_scalar_mul_si(fmpz * vec1, 
                                       const fmpz * vec2, long len2, long c);

void _fmpz_vec_scalar_mul_ui(fmpz * vec1, 
                                      const fmpz * vec2, long len2, ulong c);

void _fmpz_vec_scalar_mul_fmpz(fmpz * vec1, 
                               const fmpz * vec2, long len2, const fmpz_t x);

void _fmpz_vec_scalar_mul_2exp(fmpz * vec1, 
                                    const fmpz * vec2, long len2, ulong exp);

void _fmpz_vec_scalar_divexact_fmpz(fmpz * vec1, const fmpz * vec2, 
                                                  long len2, const fmpz_t x);

void _fmpz_vec_scalar_divexact_si(fmpz * vec1, 
                                       const fmpz * vec2, long len2, long c);

void _fmpz_vec_scalar_divexact_ui(fmpz * vec1, 
                                      const fmpz * vec2, long len2, ulong c);

void _fmpz_vec_scalar_fdiv_q_fmpz(fmpz * vec1, 
                               const fmpz * vec2, long len2, const fmpz_t c);

void _fmpz_vec_scalar_fdiv_q_si(fmpz * vec1, 
                                       const fmpz * vec2, long len2, long c);

void _fmpz_vec_scalar_fdiv_q_ui(fmpz * vec1, 
                                      const fmpz * vec2, long len2, ulong c);

void _fmpz_vec_scalar_fdiv_q_2exp(fmpz * vec1, const fmpz * vec2, 
                                                       long len2, ulong exp);

void _fmpz_vec_scalar_tdiv_q_fmpz(fmpz * vec1, 
                               const fmpz * vec2, long len2, const fmpz_t c);

void _fmpz_vec_scalar_tdiv_q_si(fmpz * vec1, 
                                       const fmpz * vec2, long len2, long c);

void _fmpz_vec_scalar_tdiv_q_ui(fmpz * vec1, 
                                      const fmpz * vec2, long len2, ulong c);

void _fmpz_vec_scalar_addmul_si(fmpz * vec1, 
                                       const fmpz * vec2, long len2, long c);

void _fmpz_vec_scalar_addmul_fmpz(fmpz * poly1, const fmpz * poly2, 
                                                  long len2, const fmpz_t x);

void _fmpz_vec_scalar_addmul_si_2exp(fmpz * vec1, const fmpz * vec2, 
                                               long len2, long c, ulong exp);

void _fmpz_vec_scalar_submul_si(fmpz * vec1, 
                                       const fmpz * vec2, long len2, long c);

void _fmpz_vec_scalar_submul_fmpz(fmpz * vec1, const fmpz * vec2, 
                                                  long len2, const fmpz_t x);

void _fmpz_vec_scalar_submul_si_2exp(fmpz * vec1, const fmpz * vec2, 
                                               long len2, long c, ulong exp);

/*  Gaussian content  ********************************************************/

void _fmpz_vec_content(fmpz_t res, const fmpz * vec, long len);

#endif

