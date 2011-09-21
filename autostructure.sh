#!/bin/bash

# We are in the top-level flint directory.
mkdir include
mv *.h include
mkdir src
for d in $(find . -maxdepth 1 -type d); do
    if test -f $d/Makefile; then mv $d src/$d; fi
done
