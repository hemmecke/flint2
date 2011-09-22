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
# This script should be run after a checkout of flint from the
# repository. It assumes that the autotools (autoconf, automake) are
# installed.
#
###################################################################

testversion() { test "$2" = "`($1 --version | head -n 1) 2>/dev/null`"; }

# Check for appropriate versions of autoconf/automake/libtool.
checkversion() {
  if
    testversion autoreconf "autoreconf (GNU Autoconf) 2.68" &&
    testversion autoconf   "autoconf (GNU Autoconf) 2.68" &&
    testversion automake   "automake (GNU automake) 1.11" &&
    testversion libtool    "libtool (GNU libtool) 2.4";
  then
    :
  else
    echo "================================================================="
    echo "You don't have the suggested versions of the autotools."
    echo "Please run"
    echo
    echo "  make -f autotools.mk"
    echo
    echo "in order to install autotools into the subdirectory 'autotools'."
    echo "Then execute"
    echo
    echo "  export PATH=`pwd`/autotools/bin:\$PATH"
    echo
    echo "to prepend the path your PATH environment variable."
    echo
    echo "Depending on your internet connection, this installation will"
    echo "take you less than 2 minutes."
    echo
    echo "Don't complain if something does not work!"
    echo "================================================================="
  fi
}

error() {
  echo "$1"
  checkversion
  exit 1
}

# Initialize the build system using the GNU AutoTools.
echo "Calling autoreconf ..."
autoreconf -i --verbose -Wall || \
    error "autoreconf could not generate all necessary files."

checkversion
