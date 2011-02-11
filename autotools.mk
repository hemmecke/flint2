###################################################################
#
# Copyright (C) 2011,  Ralf Hemmecke <ralf@hemmecke.de>
#
###################################################################
# You can redistribute this file under the terms of the
# GNU General Public License version 3 or later.
###################################################################
#
# Usage: make -f autotools.mk
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
autotools:
	-mkdir $@
	cp autotools.mk $@/Makefile
	cd $@ && ${MAKE} P="`pwd`" PATH="`pwd`/bin:${PATH}" install
	@echo
	@echo =====================================================
	@echo PATH=`pwd`/autotools/bin:\$$PATH
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
	-rm -rf $@/download

# The following targets are executed inside the directory
# "autotools/download".
autoconf automake libtool:
	-rm $@-$V.tar.gz
	wget ftp://mirrors.kernel.org/gnu/$@/$@-$V.tar.gz
	gunzip -c $@-$V.tar.gz | tar xf -
	cd $@-$V && ./configure --prefix="$P"
	cd $@-$V && make
	cd $@-$V && make install
