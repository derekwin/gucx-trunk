#include <gmem/api/gmem.h>

gmem_status_t gmem_cncl_init(unsigned group_index);
gmem_status_t gmem_cncl_alloc(void **address_p, size_t length);
gmem_status_t gmem_cncl_free(void* ptr);
gmem_status_t gmem_cncl_memcpy(void *dst,
                                 const void *src,
                                 size_t count);
gmem_status_t gmem_cncl_memset(void *dst, int value, size_t count);
