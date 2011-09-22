#!/bin/bash
###################################################################
#
# Copyright (C) 2011,  Ralf Hemmecke <ralf@hemmecke.de>
#
###################################################################
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###################################################################

# Generate headers.am from the files in the include directory.
find include -type f \
|sort \
|awk 'BEGIN{printf "include_HEADERS="};{printf "\\\n  " $1};END {print ""}'\
> headers.am

# Generate sources.am from the files in the src directory.
find src -name '*.c' ! -name 't-*.c' ! -name 'p-*.c'|grep -v '/profile/' \
|sort \
|awk 'BEGIN{printf "libflint_la_SOURCES="};{printf "\\\n  " $1};END{print ""}'\
> sources.am

# Generate tests.am from the files matching 't-*.c'.
for sd in $(find src -mindepth 1 -maxdepth 1 -type d); do
    d=$(echo $sd|sed 's|^src/||');
    find $sd -name 't-*.c' | sort \
    |(echo "TESTS += \${${d}_TESTS}"; \
      printf "%s" "${d}_TESTS ="; \
      awk '{printf "\\\n  " $1};END{print ""}')\
done > tests.am
