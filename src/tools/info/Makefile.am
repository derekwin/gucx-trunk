
bin_PROGRAMS = gucxt_info


gucxt_info_CPPFLAGS  = $(BASE_CPPFLAGS)
gucxt_info_CFLAGS    = $(BASE_CFLAGS)
gucxt_info_LDFLAGS   = -lpthread $(BASE_LDFLAGS)

noinst_HEADERS = \
	gucxt_info.h

gucxt_info_SOURCES  = \
	gucxt_info.c

gucxt_info_LDADD    = \
    $(abs_top_builddir)/src/libgmem.la'