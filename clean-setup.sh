#! /bin/sh
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
#
# This script should be run after "make maintainer-clean" in order
# to remove all the file that were produce by autogen.
#
###################################################################

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
