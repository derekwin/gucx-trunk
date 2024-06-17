#include <api/gmem.h>
#include <stdlib.h>

// const gmem_allocator_t *ga;

gmem_status_t gmem_init(unsigned group_index)
{   
    gmem_status_t ret;

    if (ga == NULL)
    {
        log_error("gucxt without valid cuda/rocm/cncl");
        return GMEM_ERROR_NO_DEVICE;
    }
    ret = ga->gmem_init(group_index);
    if (ret != GMEM_SUCCESS){
        log_error("ga->gmem_init(group_index); failed");
        return ret;
    }
    inited = 1;
    return GMEM_SUCCESS;
}

gmem_status_t gmem_alloc(void** ptr, size_t size)
{   
    if(inited){
        return ga->gmem_alloc(ptr, size);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_status_t gmem_free(void* ptr)
{ 
    if(inited){
        return ga->gmem_free(ptr);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_status_t gmem_memcpy(void* dst, const void* src, size_t size)
{
    if(inited){
        return ga->gmem_memcpy(dst, src, size);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_status_t gmem_memset(void* dst, int val, size_t size)
{
    if(inited){
        return ga->gmem_memset(dst, val, size);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_memory_type_t gmem_get_memory_type()
{
    if(inited){
        return ga->mem_type;
    }
    log_error("gmem has not been inited");
    return GMEM_MEMORY_TYPE_LAST;
}