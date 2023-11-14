AUTOMAKE_OPTIONS=foreign subdir-objects
bin_PROGRAMS=osu-utils
CommonFlags=-I$(top_srcdir)/inc -O2 -Wall -Wno-unknown-pragmas -Wno-enum-compare -Wno-deprecated-declarations -fmacro-prefix-map=$(top_srcdir)/src/=

osu_utils_CFLAGS=-std=gnu2x
osu_utils_CFLAGS+=$(CommonFlags)
osu_utils_LDADD=-lm -lcurl -lwebview

if WINDOWS
osu_utils_LDFLAGS=-static-libgcc -static-libstdc++ -Wl,-Bstatic -lpthread
endif

if LINUX
osu_utils_LDFLAGS=$(GTK_LDFLAGS) $(WEBKIT_LDFLAGS)
osu_utils_LDADD+=$(GTK_LIBS) $(WEBKIT_LIBS)
endif

if OSX
osu_utils_LDFLAGS=-L.
if ARM
# Flags for macOS ARM
osu_utils_CFLAGS+=-I/opt/homebrew/include
osu_utils_LDFLAGS=-L/opt/homebrew/lib
else
# Flags for macOS x86
osu_utils_CFLAGS+=-I/usr/local/include
osu_utils_LDFLAGS=-L/usr/local/lib
endif
endif

osu_utils_SOURCES=$(top_srcdir)/config.h $(top_srcdir)/inc/cJSON.h $(top_srcdir)/inc/log.h $(top_srcdir)/inc/webview.h $(top_srcdir)/inc/utils/core/auth/OAuth.h $(top_srcdir)/inc/utils/core/network/Downloader.h $(top_srcdir)/inc/utils/core/network/Requests.h $(top_srcdir)/inc/utils/core/op/Socket.h $(top_srcdir)/inc/utils/core/op/CalcManiaPP.h $(top_srcdir)/inc/utils/core/op/CheckScore.h $(top_srcdir)/inc/utils/core/op/GetBeatmapSets.h $(top_srcdir)/inc/utils/core/op/GetBPA.h $(top_srcdir)/inc/utils/core/op/Query.h $(top_srcdir)/inc/utils/core/profile/AccountProfile.h $(top_srcdir)/inc/utils/uic/CommandLine.h $(top_srcdir)/inc/utils/util/Generic.h $(top_srcdir)/inc/utils/extra/calc/Calc.h $(top_srcdir)/inc/utils/extra/score/Analyze.h $(top_srcdir)/inc/utils/extra/score/Score.h $(top_srcdir)/src/core/auth/OAuth.c $(top_srcdir)/src/core/network/Downloader.c $(top_srcdir)/src/core/network/Requests.c $(top_srcdir)/src/core/network/Socket.c $(top_srcdir)/src/core/op/CalcManiaPP.c $(top_srcdir)/src/core/op/CheckScore.c $(top_srcdir)/src/core/op/GetBeatmapSets.c $(top_srcdir)/src/core/op/GetBPA.c $(top_srcdir)/src/core/op/Query.c $(top_srcdir)/src/core/profile/AccountProfile.c $(top_srcdir)/src/uic/CommandLine.c $(top_srcdir)/src/util/Generic.c $(top_srcdir)/src/extra/calc/Calc.c $(top_srcdir)/src/extra/score/Analyze.c $(top_srcdir)/src/extra/score/Score.c $(top_srcdir)/src/libimpl/cJSON.c $(top_srcdir)/src/main.c
