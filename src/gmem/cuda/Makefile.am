
if HAVE_CUDA

module_LTLIBRARIES      = libgmem_cuda.la
libgmem_cuda_la_CPPFLAGS = $(BASE_CPPFLAGS) $(CUDA_CPPFLAGS)
libgmem_cuda_la_CFLAGS   = $(BASE_CFLAGS) $(CUDA_CFLAGS)
libgmem_cuda_la_LDFLAGS  = $(CUDA_LDFLAGS) $(CUDA_LIBS) -version-info $(SOVERSION)
# libgmem_cuda_la_LIBADD   = $(top_builddir)/src/gmem/libgmem.la

noinst_HEADERS = \
	cuda_mem.h

libgmem_cuda_la_SOURCES = \
	cuda_mem.c

PKG_CONFIG_NAME=cuda

include $(top_srcdir)/config/module.am

endif