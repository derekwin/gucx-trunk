
gmem_modules=""
m4_include([src/gmem/cuda/configure.m4])
m4_include([src/gmem/rocm/configure.m4])
m4_include([src/gmem/cncl/configure.m4])

AC_DEFINE_UNQUOTED([gmem_MODULES], ["${gmem_modules}"], [gmem loadable modules])

AC_CONFIG_FILES([
    src/gmem/Makefile
    src/gmem/gucxt-gmem.pc
    ])

