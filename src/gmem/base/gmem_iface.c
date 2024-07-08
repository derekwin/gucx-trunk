#include <api/gmem.h>
#include <base/gmem_iface.h>
#include <stdlib.h>

static int gucxt_inited = 0;

#if HAVE_ROCM
    #include <gmem/rocm/rocm_mem.h>
    gmem_allocator_t rocm_allocator = {
    #if MEM_MANAGED
            .mem_type  = GMEM_MEMORY_TYPE_ROCM_MANAGED,
    #else
            .mem_type  = GMEM_MEMORY_TYPE_ROCM,
    #endif
            .gmem_init      = gmem_rocm_init,
            .gmem_alloc     = gmem_rocm_alloc,
            .gmem_free      = gmem_rocm_free,
            .gmem_memcpy    = gmem_rocm_memcpy,
            .gmem_memset    = gmem_rocm_memset,
        };
    gmem_allocator_t *ga = &rocm_allocator;
#endif
#if HAVE_CUDA
    #include <gmem/cuda/cuda_mem.h>
    gmem_allocator_t cuda_allocator = {
    #if MEM_MANAGED
            .mem_type  = GMEM_MEMORY_TYPE_CUDA_MANAGED,
    #else
            .mem_type  = GMEM_MEMORY_TYPE_CUDA,
    #endif
            .gmem_init      = gmem_cuda_init,
            .gmem_alloc     = gmem_cuda_alloc,
            .gmem_free      = gmem_cuda_free,
            .gmem_memcpy    = gmem_cuda_memcpy,
            .gmem_memset    = gmem_cuda_memset,
        };
    gmem_allocator_t *ga = &cuda_allocator;
#endif
#if HAVE_CNCL
    #include <gmem/cncl/cncl_mem.h>
    gmem_allocator_t cncl_allocator = {
            .mem_type  = GMEM_MEMORY_TYPE_CNCL,
            .gmem_init      = gmem_cncl_init,
            .gmem_alloc     = gmem_cncl_alloc,
            .gmem_free      = gmem_cncl_free,
            .gmem_memcpy    = gmem_cncl_memcpy,
            .gmem_memset    = gmem_cncl_memset,
        };
    gmem_allocator_t *ga = &cncl_allocator;
#endif

gmem_status_t gmem_init(unsigned group_index)
{   
    gmem_status_t ret;

    if (ga == NULL)
    {
        log_error("gucxt without valid cuda|rocm|cncl");
        return GMEM_ERROR_NO_DEVICE;
    }
    ret = ga->gmem_init(group_index);
    if (ret != GMEM_SUCCESS){
        log_error("ga->gmem_init(group_index); failed");
        return ret;
    }
    gucxt_inited = 1;
    return GMEM_SUCCESS;
}

gmem_status_t gmem_alloc(gmem_t* mem, size_t size)
{   
    if(gucxt_inited){
        return ga->gmem_alloc(mem, size);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_status_t gmem_free(void* ptr)
{ 
    if(gucxt_inited){
        return ga->gmem_free(ptr);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_status_t gmem_memcpy(void* dst, const void* src, size_t size)
{
    if(gucxt_inited){
        return ga->gmem_memcpy(dst, src, size);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_status_t gmem_memset(void* dst, int val, size_t size)
{
    if(gucxt_inited){
        return ga->gmem_memset(dst, val, size);
    }
    log_error("gmem has not been inited");
    return GMEM_ERROR_NO_DEVICE;
}

gmem_memory_type_t gmem_get_memory_type()
{
    if(gucxt_inited){
        return ga->mem_type;
    }
    log_error("gmem has not been inited");
    return GMEM_MEMORY_TYPE_LAST;
}

char* gpudirect_driver_path_str()
{
#if HAVE_ROCM
    return "/dev/kfd";
#endif
#if HAVE_CUDA
    return "/sys/kernel/mm/memory_peers/nv_mem/version";
#endif
#if HAVE_CNCL
    return "/sys/kernel/mm/memory_peers/cambricon_peer_mem/version";
#endif
    return "";
}

char* gmem_mem_type_str()
{
    char* str = "";
    switch(gmem_get_memory_type()){
        case GMEM_MEMORY_TYPE_ROCM:
            str = "GMEM_MEMORY_TYPE_ROCM";
        case GMEM_MEMORY_TYPE_CUDA:
            str = "GMEM_MEMORY_TYPE_CUDA";
        case GMEM_MEMORY_TYPE_CNCL:
            str = "GMEM_MEMORY_TYPE_CNCL";
        default:
            break;
    }
    return str;
}

char* gmem_error_str(gmem_status_t ret)
{
    char* str = "";
    switch(ret){
        case GMEM_SUCCESS:
            str = "GMEM_SUCCESS";
        case GMEM_ERROR_CODE_INTERNAL_ERROR:
            str = "GMEM_ERROR_CODE_INTERNAL_ERROR";
        case GMEM_ERROR_CODE_INVALID_ARGUMENTS:
            str = "GMEM_ERROR_CODE_INVALID_ARGUMENTS";
        case GMEM_ERROR_NO_DEVICE:
            str = "GMEM_ERROR_NO_DEVICE";
        case GMEM_ERROR_NO_MEMORY:
            str = "GMEM_ERROR_NO_MEMORY";
        case GMEM_ERROR_MEMORY_ERROR:
            str = "GMEM_ERROR_MEMORY_ERROR";
        case GMEM_ERROR_CODE_OUT_OF_MEMORY:
            str = "GMEM_ERROR_CODE_OUT_OF_MEMORY";
        case GMEM_ERROR_CODE_NOT_IMPLEMENTED:
            str = "GMEM_ERROR_CODE_NOT_IMPLEMENTED";
        case GMEM_ERROR_CODE_NONE:
            str = "GMEM_ERROR_CODE_NONE";
        case GMEM_ERROR_CODE_LAST:
            str = "GMEM_ERROR_CODE_LAST";
        default:
            break;
    }
    return str;
}

char *string_of_memtype(gmem_memory_type_t type){
    switch(type){
        case GMEM_MEMORY_TYPE_HOST:
            return "GMEM_MEMORY_TYPE_HOST";
        case GMEM_MEMORY_TYPE_ROCM:
            return "GMEM_MEMORY_TYPE_ROCM";
        case GMEM_MEMORY_TYPE_CUDA:
            return "GMEM_MEMORY_TYPE_CUDA";
        case GMEM_MEMORY_TYPE_CNCL:
            return "GMEM_MEMORY_TYPE_CNCL";
        case GMEM_MEMORY_TYPE_ROCM_MANAGED:
            return "GMEM_MEMORY_TYPE_ROCM_MANAGED";
        case GMEM_MEMORY_TYPE_CUDA_MANAGED:
            return "GMEM_MEMORY_TYPE_CUDA_MANAGED";
        default:
            break;
    }
    return "GMEM_MEMORY_TYPE_UNKNOWN";
}