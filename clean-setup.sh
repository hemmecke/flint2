#! /bin/sh

# This script should be run after "make maintainer-clean" in order
# to remove all the file that were produce by autogen.

error() {
    echo "$1" && exit 1
}

# Remove unnecessary files.
T() {
    echo "rm $1"
    rm $1
}

# Finally, we also remove the files that have been generated by autoreconf.
T configure
find . -name Makefile.in -exec rm {} \;

# There might be several files that are autogenerated by autoreconf.
T aclocal.m4
rm -rf autom4te.cache
rm -rf config