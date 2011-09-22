# This is the main Makefile for the FLINT project.

# Make sure MPFR and MPIR and flint.h is found.
AM_CFLAGS = ${mpfr_cflags} ${mpir_cflags} -I${srcdir}/include \
  -ansi -pedantic -Wall

lib_LTLIBRARIES	    = libflint.la

# Variables connected to testing.
TESTS =            # will be defined in tests.am
XFAIL_TESTS =      # mightb be defined in tests.am
check_PROGRAMS = ${TESTS} ${XFAIL_TESTS}
LDADD = libflint.la

include headers.am # define the variable include_HEADERS
include sources.am # define the variable libflint_la_SOURCES
include tests.am   # define the variable TESTS
