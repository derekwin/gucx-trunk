
UCX_CHECK_CNCL

gmem_cncl_modules=""

AS_IF([test "x$cncl_happy" = "xyes"], [gmem_modules="${gmem_modules}:cncl"])

AC_DEFINE_UNQUOTED([gmem_cncl_MODULES], ["${gmem_cncl_modules}"], [CNCL loadable modules])

AC_CONFIG_FILES([src/gmem/cncl/Makefile
                 src/gmem/cncl/gucxt-cncl.pc])