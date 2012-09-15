AM_CFLAGS = -Wall -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-value -Wno-unused-variable -Wno-unused-function -O2 -DLOCALEDIR=\"$(localedir)\"
AM_LDFLAGS = -L/usr/local/lib -s
bin_PROGRAMS = droidpermscanner
droidpermscanner_SOURCES = droidpermscanner.l droidpermscanner_utils.c droidpermscanner_main.c ../include/droidpermscanner.h ../include/gettext.h
droidpermscanner_LDADD = $(LIBINTL)
