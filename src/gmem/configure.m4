
gmem_modules=""
m4_include([src/gmem/cuda/configure.m4])
m4_include([src/gmem/rocm/configure.m4])
m4_include([src/gmem/cncl/configure.m4])

UCX_CHECK_ROCM
UCX_CHECK_CUDA
UCX_CHECK_CNCL

AC_DEFINE_UNQUOTED([gmem_MODULES], ["${gmem_modules}"], [gmem loadable modules])

AC_CONFIG_FILES([
    src/gmem/Makefile
    src/gmem/gucxt-gmem.pc
    ])

