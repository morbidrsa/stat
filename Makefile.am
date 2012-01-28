# Copyright (c) 2012, Johannes Thumshirn

AUTOMAKE_OPTIONS = foreign 1.7

SUBDIRS = src doc

doxygen:
	doxygen && cd doc/doxygen/latex && make

test: all
	./src/test/test

version:
	@echo "Stat @VERSION@"
	@if test -d "$(top_srcdir)/.git" && test -x "`which git 2>&1;true`"; then
		echo -n "git: "; \
		(cd "$(top_srcdir)" && git rev-parse --short=16 HEAD); \
	fi