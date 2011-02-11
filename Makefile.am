# This is the main Makefile for the FLINT project.

# Make sure MPFR and MPIR and flint.h is found.
AM_CFLAGS = ${mpfr_cflags} ${mpir_cflags} -I${srcdir}/include \
  -ansi -pedantic -Wall

lib_LTLIBRARIES	    = libflint.la
libflint_la_SOURCES = # added through Rules.am

# Variables connected to testing.
check_PROGRAMS = ${TESTSUITE_TESTS} ${TESTSUITE_XFAIL_TESTS}
LDADD = libflint.la
TESTS       = ${TESTSUITE_TESTS}
XFAIL_TESTS = ${TESTSUITE_XFAIL_TESTS}
TESTSUITE_TESTS       = ${test_TESTS} # more added through Rules.am
TESTSUITE_XFAIL_TESTS = ${test_XFAIL_TESTS} # more added through Rules.am

# Include the rules from the sources subdirectories
include src/Rules.am
include test/Rules.am

include_HEADERS  = # added via include/Rules.am
include include/Rules.am
