#include <gmem/api/gmem.h>
#include <hip/hip_runtime.h>

gmem_status_t gmem_rocm_init(unsigned group_index);
gmem_status_t gmem_rocm_alloc(void **address_p, size_t length);
gmem_status_t gmem_rocm_free(void* ptr);
gmem_status_t gmem_rocm_memcpy(void *dst,
                                 const void *src,
                                 size_t count);
gmem_status_t gmem_rocm_memset(void *dst, int value, size_t count);
