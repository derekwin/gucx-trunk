
if HAVE_CNCL

module_LTLIBRARIES      = libgmem_cncl.la
libgmem_cncl_la_CPPFLAGS = $(BASE_CPPFLAGS) $(CNCL_CPPFLAGS)
libgmem_cncl_la_CFLAGS   = $(BASE_CFLAGS) $(CNCL_CFLAGS)
libgmem_cncl_la_LDFLAGS  = $(CNCL_LDFLAGS) $(CNCL_LIBS) -version-info $(SOVERSION)

noinst_HEADERS = \
	cncl_mem.h

libgmem_cncl_la_SOURCES = \
	cncl_mem.c

PKG_CONFIG_NAME=cncl

include $(top_srcdir)/config/module.am

endif