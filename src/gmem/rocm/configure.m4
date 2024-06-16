
UCX_CHECK_ROCM # 必须先运行这条，才会定义HAVE_ROCM

AS_IF([test "x$rocm_happy" = "xyes"], [gmem_modules="${gmem_modules}:rocm"])
gmem_rocm_modules=""
AC_DEFINE_UNQUOTED([gmem_rocm_MODULES], ["${gmem_rocm_modules}"], [ROCM loadable modules])
AC_CONFIG_FILES([src/gmem/rocm/Makefile
                 src/gmem/rocm/gucxt-rocm.pc])