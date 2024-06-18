#include "cuda_mem.h"

gmem_status_t gmem_cuda_init(unsigned group_index)
{
    cudaError_t cerr;
    int num_gpus;
    int gpu_index;

    cerr = cudaGetDeviceCount(&num_gpus);
    if (cerr != cudaSuccess) {
        return GMEM_ERROR_NO_DEVICE;
    }

    gpu_index = group_index % num_gpus;

    cerr = cudaSetDevice(gpu_index);
    if (cerr != cudaSuccess) {
        return GMEM_ERROR_NO_DEVICE;
    }

    /* actually set device context as calling cudaSetDevice may result in
     * context being initialized lazily */
    cudaFree(0);

    return GMEM_SUCCESS;
}

gmem_status_t gmem_cuda_alloc(void **address_p, size_t length)
{
    cudaError_t cerr;

#if MEM_MANAGED
    cerr = cudaMallocManaged(address_p, length, cudaMemAttachGlobal);
#else
    cerr = cudaMalloc(address_p, length);
#endif

    if (cerr != cudaSuccess) {
        log_error("failed to allocate memory");
        return GMEM_ERROR_NO_MEMORY;
    }

    return GMEM_SUCCESS;
}

gmem_status_t gmem_cuda_free(void* ptr)
{
    cudaFree(ptr);
    return GMEM_SUCCESS;
}

gmem_status_t gmem_cuda_memcpy(void *dst,
                                 const void *src,
                                 size_t count)
{
    cudaError_t cerr;

    cerr = cudaMemcpy(dst, src, count, cudaMemcpyDefault);
    if (cerr != cudaSuccess) {
        log_error("failed to copy memory: %s", cudaGetErrorString(cerr));
        return GMEM_ERROR_MEMORY_ERROR;
    }

    cerr = cudaDeviceSynchronize();
    if (cerr != cudaSuccess) {
        log_error("failed to sync device: %s", cudaGetErrorString(cerr));
        return GMEM_ERROR_MEMORY_ERROR;
    }

    return GMEM_SUCCESS;
}

gmem_status_t gmem_cuda_memset(void *dst, int value, size_t count)
{
    cudaError_t cerr;

    cerr = cudaMemset(dst, value, count);
    if (cerr != cudaSuccess) {
        log_error("failed to set memory: %s", cudaGetErrorString(cerr));
        return GMEM_ERROR_MEMORY_ERROR;
    }

    return GMEM_SUCCESS;
}