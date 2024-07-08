#include <gmem/api/gmem.h>

gmem_status_t gmem_cuda_init(unsigned group_index);
gmem_status_t gmem_cuda_alloc(gmem_t* mem, size_t length);
gmem_status_t gmem_cuda_free(gmem_t* mem);
gmem_status_t gmem_cuda_memcpy(void *dst,
                                 const void *src,
                                 size_t count);
gmem_status_t gmem_cuda_memset(void *dst, int value, size_t count);
