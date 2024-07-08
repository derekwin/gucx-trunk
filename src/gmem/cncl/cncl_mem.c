#include "cncl_mem.h"

#include <cnrt.h>
#include <cn_api.h> // CNresult
#include <unistd.h>

static inline const char *getErrorName(CNresult error)
{
    const char *str;
    cnGetErrorName(error, &str);
    return str;
}

static inline const char *getErrorString(CNresult error)
{
    const char *str;
    cnGetErrorString(error, &str);
    return str;
}

#define ERROR_CHECK(ret)                                                                           \
     do {                                                                                           \
         CNresult r__ = (ret);                                                                      \
         if (r__ != CN_SUCCESS) {                                                                   \
             printf(                                                                                \
                 "error occur, func: %s, line: %d, ret:%d, cn_error_code:%s, cn_error_string:%s\n", \
                 __func__, __LINE__, r__, getErrorName(r__), getErrorString(r__));                  \
             return GMEM_ERROR_NO_DEVICE;                                                                               \
         }                                                                                          \
     } while (0)

static CNdev cnDevice;
static CNcontext cnContext;

gmem_status_t gmem_cncl_init(unsigned group_index)
{
    int mlu_pci_bus_id;
	int mlu_pci_device_id;
	int index;
    int deviceCount = 0;
    int mlu_device_id;
	CNdev cn_device;
    CNresult error;
    char name[128];

	printf("initializing MLU\n");
	error = cnInit(0);
	if (error != CN_SUCCESS) {
		printf("cnInit(0) returned %d\n", error);
		return GMEM_ERROR_NO_DEVICE; 
	}

    error = cnDeviceGetCount(&deviceCount);
	if (error != CN_SUCCESS) {
		printf("cnDeviceGetCount() returned %d\n", error);
		return GMEM_ERROR_NO_DEVICE; 
	}
    if (deviceCount == 0) {
		printf("There are no available device(s) that support CUDA\n");
		return GMEM_ERROR_NO_DEVICE;
    }

    mlu_device_id = group_index % deviceCount;
	
    if (mlu_device_id >= deviceCount) {
		fprintf(stderr, "No such device ID (%d) exists in system\n", mlu_device_id);
		return GMEM_ERROR_NO_DEVICE;
	}

	printf("Listing all MLU devices in system:\n");
	for (index = 0; index < deviceCount; index++) {
		ERROR_CHECK(cnDeviceGet(&cn_device, index));
		cnDeviceGetAttribute(&mlu_pci_bus_id, CN_DEVICE_ATTRIBUTE_PCI_BUS_ID , cn_device);
		cnDeviceGetAttribute(&mlu_pci_device_id, CN_DEVICE_ATTRIBUTE_PCI_DEVICE_ID , cn_device);
		printf("MLU device %d: PCIe address is %02X:%02X\n", index, (unsigned int)mlu_pci_bus_id, (unsigned int)mlu_pci_device_id);
	}

	printf("\nPicking device No. %d\n", mlu_device_id);

    ERROR_CHECK(cnDeviceGet(&cnDevice, mlu_device_id));

	ERROR_CHECK(cnDeviceGetName(name, sizeof(name), mlu_device_id));
	printf("[pid = %d, dev = %ld] device name = [%s]\n", getpid(), cnDevice, name);
	printf("creating MLU Ctx\n");

	/* Create context */
	error = cnCtxCreate(&cnContext, 0, cnDevice);
	if (error != CN_SUCCESS) {
		printf("cnCtxCreate() error=%d\n", error);
		return GMEM_ERROR_NO_DEVICE;
	}

	printf("making it the current CUDA Ctx\n");
	error = cnCtxSetCurrent(cnContext);
	if (error != CN_SUCCESS) {
		printf("cnCtxSetCurrent() error=%d\n", error);
		return GMEM_ERROR_NO_DEVICE;
	}

    return GMEM_SUCCESS;
}

gmem_status_t gmem_cncl_alloc(gmem_t* mem, size_t length)
{
    // CNaddr mlu_addr;  mem->dri_addr
    CNresult error;
    const size_t gpu_page_size = 64 * 1024;
    size_t size = (length + gpu_page_size - 1) &
        ~(gpu_page_size - 1);

    printf("cnMallocPeerAble() of a %lu bytes MLU buffer\n",
            length);
    error = cnMallocPeerAble(&(mem->dri_addr), size);
    if (error != CN_SUCCESS) {
        printf("cnMallocPeerAble error=%d\n", error);
        return GMEM_ERROR_NO_MEMORY;
    }

    printf("allocated %zu bytes of MLU buffer at %ld\n", size, mem->dri_addr);
    mem->ptr = (void *)mem->dri_addr; // ?
    return GMEM_SUCCESS;
}

gmem_status_t gmem_cncl_free(gmem_t *mem)
{   
    printf("deallocating RX MLU buffer %ld\n", (CNaddr)mem->ptr);
    cnFree((CNaddr)mem->ptr);
    mem->dri_addr=0;
    
    printf("destroying current MLU Ctx\n");
	ERROR_CHECK(cnCtxDestroy(cnContext));
    return GMEM_SUCCESS;
}

gmem_status_t gmem_cncl_memcpy(void *dst,
                                 const void *src,
                                 size_t count)
{
    CNaddr dst_a = (CNaddr)dst;
    CNaddr src_a = (CNaddr)src;
    CNresult ret = cnMemcpy(dst_a, src_a, (cn_uint64_t)count+1); // 结束符
    
    if (ret != CN_SUCCESS) {
        log_error("failed to cp memory %d", ret);
        return GMEM_ERROR_MEMORY_ERROR;
    }

    return GMEM_SUCCESS;
}

gmem_status_t gmem_cncl_memset(void *dst, int value, size_t count)
{
    CNaddr dst_a = (CNaddr)dst;
    CNresult ret = cnMemsetD8(dst_a, value, count);
    if (ret != CN_SUCCESS) {
        const char** str = NULL;
        cnGetErrorString(ret, str);
        log_error("failed to set memory: %s", *str);
        return GMEM_ERROR_MEMORY_ERROR;
    }

    return GMEM_SUCCESS;
}

// cncl memcpy 存在问题
// cncl 的mem无法直接被printf