dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(aubiolv2, 0.1)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

if test "x$prefix" = "xNONE"; then 
  prefix=$ac_default_prefix
fi


AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_PROG_CC

AC_HEADER_STDC
AC_CHECK_HEADERS([string.h stdlib.h stdio.h])

AC_DISABLE_STATIC
AM_PROG_LIBTOOL


PKG_CHECK_MODULES(AUBIOLV2, [aubio lv2core])

AC_MSG_CHECKING(where to install LV2 plugins)
AC_ARG_WITH(lv2_dir,
  AC_HELP_STRING([--with-lv2-dir],[install LV2 bundle aubio.lv2 to DIR (default=$prefix/lib/lv2/)]),
  ,
  [with_lv2_dir="$prefix/lib/lv2/"])
AC_MSG_RESULT($with_lv2_dir)
AC_SUBST(with_lv2_dir)


AC_OUTPUT([
Makefile
src/Makefile
])
