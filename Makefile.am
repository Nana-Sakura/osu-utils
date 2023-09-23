AUTOMAKE_OPTIONS=foreign subdir-objects
bin_PROGRAMS=osu-utils
CommonFlags=-I$(top_srcdir)/inc -O2 -Wall -Wno-unknown-pragmas -Wno-enum-compare -Wno-deprecated-declarations -fmacro-prefix-map=$(top_srcdir)/src/=

AM_CFLAGS=-std=c2x
AM_CFLAGS+=$(CommonFlags)
osu_utils_LDADD=-lcurl

osu_utils_SOURCES=$(top_srcdir)/config.h $(top_srcdir)/inc/cJSON.h $(top_srcdir)/inc/log.h $(top_srcdir)/inc/utils/core/auth/OAuth.h $(top_srcdir)/inc/utils/core/network/Basic.h $(top_srcdir)/inc/utils/core/network/Downloader.h $(top_srcdir)/inc/utils/core/network/Getbplist.h $(top_srcdir)/inc/utils/core/op/Mode.h $(top_srcdir)/src/core/auth/OAuth.c $(top_srcdir)/src/core/network/Basic.c $(top_srcdir)/src/core/network/Downloader.c $(top_srcdir)/src/core/network/Getbplist.c $(top_srcdir)/src/core/op/Mode.c $(top_srcdir)/src/libimpl/cJSON.c $(top_srcdir)/src/main.c
