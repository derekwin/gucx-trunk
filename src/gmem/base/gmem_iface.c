#include <api/gmem.h>

const gmem_allocator_t *ga = NULL;

gmem_status_t gmem_init(unsigned group_index)
{
    if (ga == NULL)
    {
        log_error("need build gucxt with cuda/rocm/cncl");
        return GMEM_ERROR_NO_DEVICE;
    }
    return ga->gmem_init(group_index);
}

gmem_status_t gmem_alloc(void** ptr, size_t size)
{
    return ga->gmem_alloc(ptr, size);
}

gmem_status_t gmem_free(void* ptr)
{
    return ga->gmem_free(ptr);
}

gmem_status_t gmem_memcpy(void* dst, const void* src, size_t size)
{
    return ga->gmem_memcpy(dst, src, size);
}

gmem_status_t gmem_memset(void* dst, int val, size_t size)
{
    return ga->gmem_memset(dst, val, size);
}

gmem_memory_type_t gmem_get_memory_type()
{
    return ga->mem_type;
}