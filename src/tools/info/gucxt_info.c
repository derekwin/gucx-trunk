#include "gucxt_info.h"

int main()
{
    int gourp_id = 0;
    gmem_status_t status;

    status = gmem_init(gourp_id);
    if (status != GMEM_SUCCESS) {
        printf("gmem_init failed\n");
    }

    printf("hello gucxt_info\n");
}