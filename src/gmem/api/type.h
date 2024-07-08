#ifndef GMEM_TYPES_H_
#define GMEM_TYPES_H_

typedef enum gmem_status {
    GMEM_SUCCESS,
    GMEM_ERROR_CODE_NONE,
    GMEM_ERROR_CODE_INVALID_ARGUMENTS,
    GMEM_ERROR_NO_DEVICE,
    GMEM_ERROR_NO_MEMORY,
    GMEM_ERROR_MEMORY_ERROR,
    GMEM_ERROR_CODE_OUT_OF_MEMORY,
    GMEM_ERROR_CODE_NOT_IMPLEMENTED,
    GMEM_ERROR_CODE_INTERNAL_ERROR,
    GMEM_ERROR_CODE_LAST
} gmem_status_t;

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

#endif /* GMEM_TYPES_H_ */