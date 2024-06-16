

UCX_CHECK_CUDA

AS_IF([test "x$cuda_happy" = "xyes"], [gmem_modules="${gmem_modules}:cuda"])
gmem_cuda_modules = ""
AC_DEFINE_UNQUOTED([gmem_cuda_MODULES], ["${gmem_cuda_modules}"], [CUDA loadable modules])
AC_CONFIG_FILES([src/gmem/cuda/Makefile
                 src/gmem/cuda/gucxt-cuda.pc])
