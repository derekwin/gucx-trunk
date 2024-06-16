
if HAVE_CNCL

module_LTLIBRARIES      = libgmem_cncl.la
libgmem_cncl_la_CPPFLAGS = $(BASE_CPPFLAGS) $(CNCL_CPPFLAGS)
libgmem_cncl_la_CFLAGS   = $(BASE_CFLAGS) $(CNCL_CFLAGS)
libgmem_cncl_la_LDFLAGS  = $(CNCL_LDFLAGS) -version-info $(SOVERSION)
libgmem_cncl_la_LIBADD   = $(top_builddir)/src/libgmem.la

noinst_HEADERS =

libgmem_cncl_la_SOURCES = \
	cncl_mem.c

PKG_CONFIG_NAME=cncl

include $(top_srcdir)/config/module.am

endif