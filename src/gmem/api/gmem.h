#ifndef GMEM_H_
#define GMEM_H_

#include "type.h"
#include "log.h"

#ifdef _MSC_VER
typedef unsigned __int64 cn_uint64_t;
typedef __int64 cn_int64_t;
typedef unsigned __int32 cn_uint32_t;
#else
#include <stdint.h>
typedef uint64_t cn_uint64_t;
typedef int64_t cn_int64_t;
typedef uint32_t cn_uint32_t;
#endif
typedef __SIZE_TYPE__ size_t;

typedef cn_uint64_t GMEMaddr;

typedef enum gmem_memory_type {
    GMEM_MEMORY_TYPE_HOST,          /**< Default system memory */
    GMEM_MEMORY_TYPE_CUDA,          /**< NVIDIA CUDA memory */
    GMEM_MEMORY_TYPE_CUDA_MANAGED,  /**< NVIDIA CUDA managed (or unified) memory */
    GMEM_MEMORY_TYPE_CNCL,          /**< MLU CNCL memory */
    GMEM_MEMORY_TYPE_ROCM,          /**< AMD ROCM memory */
    GMEM_MEMORY_TYPE_ROCM_MANAGED,  /**< AMD ROCM managed system memory */
    GMEM_MEMORY_TYPE_LAST
} gmem_memory_type_t;

char* gmem_memory_type_list[] = {
    "HOST",
    "CUDA",
    "CUDA_MANAGED",
    "CNCL",
    "ROCM",
    "ROCM_MANAGED"
};

char *string_of_memtype(gmem_memory_type_t type){
    return gmem_memory_type_list[type];
}

typedef gmem_status_t (*gmem_init_func_t)(unsigned group_index);
typedef gmem_status_t (*gmem_alloc_func_t)(void** ptr, size_t size);  /* 后续考虑cncl模式 */
typedef gmem_status_t (*gmem_free_func_t)(void* ptr);
typedef gmem_status_t (*gmem_memcpy_func_t)(void* dst, const void* src, size_t size);
typedef gmem_status_t (*gmem_memset_func_t)(void* dst, int val, size_t size);

int inited = 0;

typedef struct gmem_allocator {
    gmem_memory_type_t      mem_type;
    gmem_init_func_t        gmem_init;
    gmem_alloc_func_t       gmem_alloc;
    gmem_free_func_t        gmem_free;
    gmem_memcpy_func_t      gmem_memcpy;
    gmem_memset_func_t      gmem_memset;
} gmem_allocator_t;

/* Allocators for each memory type */
// #define NUM_GMEM_ALLOCATOR 1
// #define DEFAULT_GMEM_ALLOCATOR 0
gmem_allocator_t *ga = NULL;

extern gmem_status_t gmem_init(unsigned group_index);
extern gmem_status_t gmem_alloc(void** ptr, size_t size);
extern gmem_status_t gmem_free(void* ptr);
extern gmem_status_t gmem_memcpy(void* dst, const void* src, size_t size);
extern gmem_status_t gmem_memset(void* dst, int val, size_t size);
extern gmem_memory_type_t gmem_get_memory_type(void);

/* Unique value generator */
#ifdef __COUNTER__
#  define UCS_PP_UNIQUE_ID __COUNTER__
#else
#  define UCS_PP_UNIQUE_ID __LINE__
#endif
/* Paste two expanded tokens */
#define UCS_PP_TOKENPASTE(x, y)           x ## y
#define UCS_F_CTOR __attribute__((constructor))
/* Creating unique identifiers, used for macros */
#define UCS_PP_APPEND_UNIQUE_ID(x)        UCS_PP_TOKENPASTE(x, UCS_PP_UNIQUE_ID)
#define UCS_STATIC_INIT \
    static void UCS_F_CTOR UCS_PP_APPEND_UNIQUE_ID(ucs_initializer_ctor)()

#endif /* GMEM_H_ */