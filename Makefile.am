AM_CPPFLAGS = -I$(top_srcdir)/src/include

bin_PROGRAMS = src/bin/wpmgr
src_bin_wpmgr_SOURCES = \
	src/bin/http.cpp \
	src/bin/main.cpp
src_bin_wpmgr_LDADD = -ltinfo -lncurses -lcurl
src_bin_wpmgr_CFLAGS = -Werror -Wall
