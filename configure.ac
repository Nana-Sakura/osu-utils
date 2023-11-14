#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([osu-utils],[1.0],[wxkj123])
AC_CONFIG_SRCDIR([src/Main.cc])
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
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
AC_CHECK_HEADERS([arpa/inet.h curl/curl.h netinet/in.h stdint.h sys/socket.h])

# Checks for typedefs, structures, and compiler characteristics.

AC_TYPE_SSIZE_T
AC_TYPE_SIZE_T
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_TYPE_MODE_T
AC_CHECK_MEMBERS([struct stat.st_mtimespec.tv_sec])
AC_CHECK_MEMBERS([struct stat.st_size])

# Checks for library functions.

AC_OUTPUT
