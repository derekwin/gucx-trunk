
# SUBDIRS = . cuda rocm cncl tools/info
SUBDIRS = cuda rocm .  # build submodule first

nobase_dist_libgmem_la_HEADERS = \
	api/gmem.h

noinst_HEADERS = \
    base/gmem_iface.h

libgmem_la_SOURCES = \
    base/gmem_iface.c

lib_LTLIBRARIES    = libgmem.la
libgmem_la_CFLAGS   = $(BASE_CFLAGS)
libgmem_la_CPPFLAGS = $(BASE_CPPFLAGS)
libgmem_la_LDFLAGS  = -ldl -version-info $(SOVERSION)
libgmem_ladir       = $(includedir)/gmem

if HAVE_ROCM
    libgmem_la_CFLAGS   += -DHAVE_ROCM
    libgmem_la_LIBADD   = $(top_builddir)/src/gmem/rocm/libgmem_rocm.la
endif
if HAVE_CUDA
    libgmem_la_CFLAGS   += -DHAVE_CUDA
    libgmem_la_LIBADD   = $(top_builddir)/src/gmem/cuda/libgmem_cuda.la
endif
if HAVE_CNCL
    libgmem_la_CFLAGS   += -DHAVE_CNCL
endif



PKG_CONFIG_NAME=gmem

include $(top_srcdir)/config/module-pkg-config.am