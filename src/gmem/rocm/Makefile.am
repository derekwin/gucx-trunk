if HAVE_ROCM

module_LTLIBRARIES      = libgmem_rocm.la
libgmem_rocm_la_CPPFLAGS = $(BASE_CPPFLAGS) $(ROCM_CPPFLAGS)
libgmem_rocm_la_CFLAGS   = $(BASE_CFLAGS)
libgmem_rocm_la_LDFLAGS  = $(ROCM_LDFLAGS) $(ROCM_LIBS) -version-info $(SOVERSION) \
                          $(patsubst %, -Xlinker %, -L$(ROCM_ROOT)/lib -rpath $(ROCM_ROOT)/hip/lib -rpath $(ROCM_ROOT)/lib) \
                          $(patsubst %, -Xlinker %, --enable-new-dtags) \
                          $(patsubst %, -Xlinker %, -rpath $(ROCM_ROOT)/lib64)

noinst_HEADERS = \
    rocm_mem.h

libgmem_rocm_la_SOURCES = \
    rocm_mem.c

PKG_CONFIG_NAME=rocm

include $(top_srcdir)/config/module.am

endif