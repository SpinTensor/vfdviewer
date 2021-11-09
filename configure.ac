AC_INIT([vfdviewer], [0.0.1], [felix.uhl@emea.nec.com])
: ${CFLAGS="-O3"}

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

# enable Debug output
AC_ARG_ENABLE(
   [debug],
   [AS_HELP_STRING([--enable-debug],[build with additional debugging code [default=no]])],
   [enable_debug="yes"],
   [enable_debug="no"])
AM_CONDITIONAL(
   [ENABLE_DEBUG],
   [test "$enable_debug" = yes])
AM_COND_IF(
   [ENABLE_DEBUG],
   [AX_APPEND_FLAG([-g])
    AX_APPEND_FLAG([-D_DEBUG])])

# enable building of textlogn viewer
AC_ARG_ENABLE(
   [vfdviewer],
   [AS_HELP_STRING([--enable-vfdviewer],[build with the gtk based viewer for vfdfiles [default=yes]])],
   [],
   [enable_vfdviewer="yes"])
AM_CONDITIONAL(
   [ENABLE_VFDVIEWER],
   [test "$enable_vfdviewer" = yes])

# enable building of textlogn viewer
AC_ARG_ENABLE(
   [logviewer],
   [AS_HELP_STRING([--enable-logviewer],[build with the ncurses based viewer for text logfiles [default=yes]])],
   [],
   [enable_logviewer="yes"])
AM_CONDITIONAL(
   [ENABLE_LOGVIEWER],
   [test "$enable_logviewer" = yes])

# check for gtk
PKG_CHECK_MODULES(
   [GTK],
   [gtk+-3.0 >= 3.0],
   [has_gtk_pkg="yes"],
   [has_gtk_pkg="no"])
AM_CONDITIONAL(
   [HAS_GTK_PKG],
   [test "$has_gtk_pkg" = yes])

# check for ncurses
PKG_CHECK_MODULES(
   [NCURSES],
   [ncurses],
   [has_ncurses_pkg="yes"],
   [has_ncurses_pkg="no"])
AM_CONDITIONAL(
   [HAS_NCURSES_PKG],
   [test "$has_ncurses_pkg" = yes])

# check vfdviewer and gtk consistency
AM_COND_IF(
   [ENABLE_LOGVIEWER],
   [AM_COND_IF(
      [HAS_GTK_PKG],
      [],
      [AC_MSG_FAILURE([vfdviewer requires GTK+-3 library. Install GTK, or disable vfdviewer compilation.])])])

# check logviewer and ncurses consistency
AM_COND_IF(
   [ENABLE_LOGVIEWER],
   [AM_COND_IF(
      [HAS_NCURSES_PKG],
      [],
      [AC_MSG_FAILURE([Logviewer requires NCURSES library. Install NCURSES, or disable logviewer compilation.])])])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([src/vfdviewer/Makefile])
AC_CONFIG_FILES([src/logviewer/Makefile])
AC_CONFIG_FILES([test/Makefile])
AC_CONFIG_FILES([external/Makefile])

AC_OUTPUT
