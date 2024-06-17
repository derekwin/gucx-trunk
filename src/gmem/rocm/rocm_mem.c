#include <gmem/api/gmem.h>
#include <hip/hip_runtime.h>

static gmem_status_t gmem_rocm_init(unsigned group_index)
{
    hipError_t ret;
    int num_gpus;
    int gpu_index;

    ret = hipGetDeviceCount(&num_gpus);
    if (ret != hipSuccess) {
        return GMEM_ERROR_NO_DEVICE;
    }

    gpu_index = group_index % num_gpus;

    ret = hipSetDevice(gpu_index);
    if (ret != hipSuccess) {
        return GMEM_ERROR_NO_DEVICE;
    }

    return GMEM_SUCCESS;
}

static inline gmem_status_t gmem_rocm_alloc(void **address_p, size_t length)
{
    hipError_t ret;

#if MEM_MANAGED
    ret = hipMallocManaged(address_p, length, hipMemAttachGlobal);
#else
    ret = hipMalloc(address_p, length);
#endif

    if (ret != hipSuccess) {
        log_error("failed to allocate memory");
        return GMEM_ERROR_NO_MEMORY;
    }

    return GMEM_SUCCESS;
}

static gmem_status_t gmem_rocm_free(void* ptr)
{
    hipFree(ptr);
    return GMEM_SUCCESS;
}

static gmem_status_t gmem_rocm_memcpy(void *dst,
                                 const void *src,
                                 size_t count)
{
    hipError_t ret;

    ret = hipMemcpy(dst, src, count, hipMemcpyDefault);
    if (ret != hipSuccess) {
        log_error("failed to copy memory: %s", hipGetErrorString(ret));
        return GMEM_ERROR_MEMORY_ERROR;
    }
    return GMEM_SUCCESS;
}

static gmem_status_t gmem_rocm_memset(void *dst, int value, size_t count)
{
    hipError_t ret;

    ret = hipMemset(dst, value, count);
    if (ret != hipSuccess) {
        log_error("failed to set memory: %s", hipGetErrorString(ret));
        return GMEM_ERROR_MEMORY_ERROR;
    }

    return GMEM_SUCCESS;
}


UCS_STATIC_INIT {
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
    ga = &rocm_allocator;
}