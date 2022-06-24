AM_CPPFLAGS = -I$(top_srcdir)/src/include \
			  -I/usr/include

bin_PROGRAMS = wpmgr
wpmgr_SOURCES = \
	src/bin/http.cpp \
	src/bin/chan.cpp \
	src/bin/ui.cpp \
	src/bin/main.cpp
wpmgr_LDADD = -ltinfo -lncurses -lmenu -lcurl
wpmgr_CXXFLAGS = -std=c++17 -Werror -Wall
