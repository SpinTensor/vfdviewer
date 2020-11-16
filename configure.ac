AC_INIT([vfdviewer], [0.0.1], [felix.uhl@emea.nec.com])
: ${CFLAGS="-O2"}
: ${CXXFLAGS="-O2"}
: ${FCFLAGS="-O2"}

# Will be generated
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign no-dependencies subdir-objects])
AC_PROG_CC
AM_PROG_AR
LT_INIT
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Check if C-compiler supports c99 standard
AX_CHECK_C99_STD

# check for gtk
PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.0])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT
