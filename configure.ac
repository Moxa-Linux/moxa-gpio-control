# moxa-gpio-control version
m4_define([version_major], [1])
m4_define([version_minor], [0])
m4_define([version_revision], [2])
m4_define([version_code], [version_major.version_minor.version_revision])

# autoconf, automake, libtool initial
AC_PREREQ(2.69)
AC_INIT([moxa-gpio-control], [version_code])
AM_INIT_AUTOMAKE

AM_SILENT_RULES([yes])

AC_PROG_CC
AC_PROG_MKDIR_P
AC_PROG_INSTALL

LT_PREREQ(2.4)
LT_INIT([disable-static])

VERSION_CODE=version_code
AC_SUBST(VERSION_CODE)

# check libraries & headers
AC_DEFUN([FUNC_NOT_FOUND_LIB],
	[AC_MSG_ERROR([function $1 not found])])
AC_DEFUN([HEADER_NOT_FOUND_LIB],
	[AC_MSG_ERROR([header $1 not found])])

AC_CHECK_HEADERS([stdio.h], [], [HEADER_NOT_FOUND_LIB([stdio.h])])
AC_CHECK_HEADERS([unistd.h], [], [HEADER_NOT_FOUND_LIB([unistd.h])])
AC_CHECK_HEADERS([fcntl.h], [], [HEADER_NOT_FOUND_LIB([fcntl.h])])
AC_CHECK_HEADERS([string.h], [], [HEADER_NOT_FOUND_LIB([string.h])])
AC_CHECK_HEADERS([errno.h], [], [HEADER_NOT_FOUND_LIB([errno.h])])

# output
AC_CONFIG_FILES([
	include/Makefile
	lib/Makefile
	Makefile
])
AC_OUTPUT
