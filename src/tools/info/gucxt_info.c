#include "gucxt_info.h"

int main()
{
    int gourp_id = 0;
    gmem_status_t status;

    status = gmem_init(gourp_id);
    if (status != GMEM_SUCCESS) {
        return 0;
    }

    printf("%s\n", string_of_memtype(gmem_get_memory_type()));

    printf("hello gucxt_info\n");
}