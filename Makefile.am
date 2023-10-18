AUTOMAKE_OPTIONS=foreign subdir-objects
bin_PROGRAMS=osu-utils
CommonFlags=-I$(top_srcdir)/inc -O2 -Wall -Wno-unknown-pragmas -Wno-enum-compare -Wno-deprecated-declarations -fmacro-prefix-map=$(top_srcdir)/src/=

AM_CFLAGS=-std=c2x
AM_CFLAGS+=$(CommonFlags)
osu_utils_LDADD=-lcurl

osu_utils_SOURCES=$(top_srcdir)/config.h $(top_srcdir)/inc/cJSON.h $(top_srcdir)/inc/log.h $(top_srcdir)/inc/utils/core/auth/OAuth.h $(top_srcdir)/inc/utils/core/network/Downloader.h $(top_srcdir)/inc/utils/core/network/Requests.h $(top_srcdir)/inc/utils/core/op/Socket.h $(top_srcdir)/inc/utils/core/op/CalcManiaPP.h $(top_srcdir)/inc/utils/core/op/CheckScore.h $(top_srcdir)/inc/utils/core/op/GetBeatmapSets.h $(top_srcdir)/inc/utils/core/op/GetBPA.h $(top_srcdir)/inc/utils/core/op/Query.h $(top_srcdir)/inc/utils/core/profile/AccountProfile.h $(top_srcdir)/inc/utils/core/uic/CommandLine.h $(top_srcdir)/inc/utils/core/util/Generic.h $(top_srcdir)/inc/utils/extra/calc/Calc.h $(top_srcdir)/inc/utils/extra/score/Analyze.h $(top_srcdir)/inc/utils/extra/score/Score.h $(top_srcdir)/src/core/auth/OAuth.c $(top_srcdir)/src/core/network/Downloader.c $(top_srcdir)/src/core/network/Requests.c $(top_srcdir)/src/core/network/Socket.c $(top_srcdir)/src/core/op/CalcManiaPP.c $(top_srcdir)/src/core/op/CheckScore.c $(top_srcdir)/src/core/op/GetBeatmapSets.c $(top_srcdir)/src/core/op/GetBPA.c $(top_srcdir)/src/core/op/Query.c $(top_srcdir)/src/core/profile/AccountProfile.c $(top_srcdir)/src/core/uic/CommandLine.c $(top_srcdir)/src/core/util/Generic.c $(top_srcdir)/src/extra/calc/Calc.c $(top_srcdir)/src/extra/score/Analyze.c $(top_srcdir)/src/extra/score/Score.c $(top_srcdir)/src/libimpl/cJSON.c $(top_srcdir)/src/main.c
