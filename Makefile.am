# This is the main Makefile for the FLINT project.

lib_LTLIBRARIES	    = libflint.la
libflint_la_SOURCES = # added through Rules.am

# Include the rules from the sources subdirectories
include src/Rules.am
## for d in $(find src -maxdepth 1 -mindepth 1 -type d); do (echo === src/$d ===; cd $d; (echo "libflint_la_SOURCES += \\"; for f in $(ls *.c); do echo "  $d/$f \\"; done; echo) > Rules.am); done

include_HEADERS  = # added via include/Rules.am
include include/Rules.am
