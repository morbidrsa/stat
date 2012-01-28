TESTS = test

noinst_PROGRAMS = test

AM_CPPFLAGS = -I"$(top_srcdir)/src/csv"

test_SOURCES = 			\
	test.c 			\
	tinytest.c

test_LDADD = ../csv/libstat-csv.a

noinst_HEADERS = 			\
	tinytest.h 			\
	tinytest_macros.h