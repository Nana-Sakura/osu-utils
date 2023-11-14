AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=osu-utils
CommonFlags=-I$(top_srcdir)/inc -O2 -Wall -Wno-unknown-pragmas -Wno-enum-compare -Wno-deprecated-declarations -fmacro-prefix-map=$(top_srcdir)/src/=

AM_CFLAGS=-std=gnu2x
AM_CXXFLAGS=$(CommonFlags)
AM_CFLAGS+=$(CommonFlags)

osu_utils_LDADD=-lm -lcurl

if WINDOWS
AM_CXXFLAGS+=-std=c++23
AM_CFLAGS+=-DCURL_STATICLIB
osu_utils_LDADD+=-lws2_32 -lshell32 -lshlwapi -luser32
osu_utils_LDFLAGS=-static-libstdc++ -static-libgcc -lpthread
endif

if LINUX
AM_CXXFLAGS+=-std=c++2b
endif

if OSX
AM_CXXFLAGS+=-std=c++2b

if ARM
# Flags for macOS ARM
AM_CXXFLAGS+=-I/opt/homebrew/include
AM_CFLAGS+=-I/opt/homebrew/include
osu_utils_LDFLAGS=-L/opt/homebrew/lib
else
# Flags for macOS x86
AM_CXXFLAGS+=-I/usr/local/include
AM_CFLAGS+=-I/usr/local/include
osu_utils_LDFLAGS=-L/usr/local/lib
endif
endif

osu_utils_SOURCES=$(top_srcdir)/build/config.h $(top_srcdir)/inc/cJSON.h $(top_srcdir)/inc/utils/core/auth/ClientCredential.hh $(top_srcdir)/inc/utils/core/auth/AuthorizationCodeGrant.hh $(top_srcdir)/inc/utils/core/op/GetBeatmapSets.hh $(top_srcdir)/inc/utils/core/op/Query.hh $(top_srcdir)/inc/utils/core/op/Token.hh $(top_srcdir)/inc/utils/core/op/GetBPA.hh $(top_srcdir)/inc/utils/core/op/CheckScore.hh $(top_srcdir)/inc/utils/core/network/Requests.hh $(top_srcdir)/inc/utils/core/network/Socket.hh $(top_srcdir)/inc/utils/core/network/Download.hh $(top_srcdir)/inc/utils/core/score/Analyze.hh $(top_srcdir)/inc/utils/core/score/ParseScore.hh $(top_srcdir)/inc/utils/core/profile/AccountProfile.hh $(top_srcdir)/inc/utils/util/Commons.hh $(top_srcdir)/inc/utils/uic/Brain.hh $(top_srcdir)/inc/utils/uic/CommandLine.hh $(top_srcdir)/inc/utils/extra/calc/CalcManiaPP.hh $(top_srcdir)/inc/log.hh $(top_srcdir)/src/Main.cc $(top_srcdir)/src/core/auth/AuthorizationCodeGrant.cc $(top_srcdir)/src/core/auth/ClientCredential.cc $(top_srcdir)/src/core/op/GetBeatmapSets.cc $(top_srcdir)/src/core/op/GetBPA.cc $(top_srcdir)/src/core/op/CheckScore.cc $(top_srcdir)/src/core/op/Query.cc $(top_srcdir)/src/core/op/Token.cc $(top_srcdir)/src/core/network/Requests.cc $(top_srcdir)/src/core/network/Socket.cc $(top_srcdir)/src/core/network/Download.cc $(top_srcdir)/src/core/score/Analyze.cc $(top_srcdir)/src/core/score/ParseScore.cc $(top_srcdir)/src/core/profile/AccountProfile.cc $(top_srcdir)/src/util/Commons.cc $(top_srcdir)/src/uic/CommandLine.cc $(top_srcdir)/src/extra/calc/CalcManiaPP.cc $(top_srcdir)/src/libimpl/cJSON.c
