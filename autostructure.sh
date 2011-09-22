#!/bin/bash

# We are in the top-level flint directory.
mkdir include
mv *.h include
mkdir src
for d in $(find . -maxdepth 1 -type d); do
    if test -f $d/Makefile; then mv $d src/$d; fi
done

# Remove Makefiles and configure.
find . -name Makefile -delete
rm Makefile.in
rm configure

# Move top-level code to src/aux.
mkdir src/aux
mv test *.c src/aux