# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([osu-utils], [0.1], [wxkj123])
AC_CONFIG_SRCDIR([src/main.c])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# Check for compiler
AC_PROG_CC

# Checks for system.
AC_CANONICAL_HOST

build_linux=no
build_windows=no
build_mac=no
build_arm=no

case "${host_cpu}" in
    arm*|aarch*)
        build_arm=yes
        ;;
esac

case "${host_os}" in
    linux*)
        build_linux=yes
        ;;
    cygwin*|mingw*)
        build_windows=yes
        ;;
    darwin*)
        build_mac=yes
        ;;
    *)
        AC_MSG_ERROR(["OS $host_os is not supported"])
        ;;
esac

AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])
AM_CONDITIONAL([OSX], [test "$build_mac" = "yes"])
AM_CONDITIONAL([ARM], [test "$build_arm" = "yes"])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([curl/curl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.

AC_OUTPUT
