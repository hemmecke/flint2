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
# Usage:
#   make -f autotools.mk
#   make -f autotools.mk PREFIX=/path/to/install/dir
#
# If PREFIX is missing it is equivalent to PREFIX=`pwd`/autotools.
#
# Purpose: Install autotools locally into a newly created
# subdirectory autotools/.
#
# Temporarily a subdirectory autotools/download is created, but
# that will be removed after successful installation.
# The script requires Internet access to run.
# After installation, the new autotools are available via
#   PATH=`pwd`/autotools/bin:$PATH
###################################################################
.PHONY: autotools all automake autoconf libtool

# Specify the default installation directory.
PREFIX=`pwd`/autotools

autotools:
	@if test "$$(echo ${PREFIX} | sed -e 's,^/.*,/,')" != "/"; then \
	  echo "PREFIX must be an absolute path."; \
	  exit 1; \
	fi
	-mkdir $@
	cp autotools.mk $@/Makefile
	${MAKE} -C $@ PREFIX=${PREFIX} PATH="${PREFIX}/bin:${PATH}" install
	@echo
	@echo =====================================================
	@echo
	@echo Add the following to your shell configuration file:
	@echo
	@echo PATH=${PREFIX}/bin:\$$PATH
	@echo export PATH
	@echo

# The following target is called only in directory "autotools".
# We assume that the variable P contains the full path to the
# "autotools" subdirectory.
install:
	-mkdir download
	cp Makefile download/Makefile
	cd download && ${MAKE} autoconf V=2.68
	cd download && ${MAKE} automake V=1.11
	cd download && ${MAKE} libtool  V=2.4
	-rm -rf download

# The following targets are executed inside the directory
# "autotools/download".
autoconf automake libtool:
	-rm $@-$V.tar.gz
	wget ftp://ftp.gnu.org/gnu/$@/$@-$V.tar.gz
	gunzip -c $@-$V.tar.gz | tar xf -
	cd $@-$V && ./configure --prefix="${PREFIX}"
	cd $@-$V && make
	cd $@-$V && make install
