
# SUBDIRS = . cuda rocm cncl tools/info
SUBDIRS = . cuda rocm

lib_LTLIBRARIES    = libgmem.la
libgmem_la_CFLAGS   = $(BASE_CFLAGS)
libgmem_la_CPPFLAGS = $(BASE_CPPFLAGS)
libgmem_la_LDFLAGS  = -ldl -version-info $(SOVERSION)
libgmem_ladir       = $(includedir)/gmem

nobase_dist_libgmem_la_HEADERS = \
	api/gmem.h

noinst_HEADERS =

libgmem_la_SOURCES = \
    base/gmem_iface.c

PKG_CONFIG_NAME=gmem

include $(top_srcdir)/config/module-pkg-config.am