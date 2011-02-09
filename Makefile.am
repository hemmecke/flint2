# This is the main Makefile for the FLINT project.

# Make sure MPFR and MPIR and flint.h is found.
AM_CFLAGS = ${mpfr_cflags} ${mpir_cflags} -I${srcdir}/include \
  -ansi -pedantic -Wall

lib_LTLIBRARIES	    = libflint.la
libflint_la_SOURCES = # added through Rules.am

# Include the rules from the sources subdirectories
include src/Rules.am

include_HEADERS  = # added via include/Rules.am
include include/Rules.am
