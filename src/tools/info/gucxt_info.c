#include "gucxt_info.h"
#include <string.h>

int main()
{
    int gourp_id = 0;
    gmem_status_t status;
    void *p = NULL;
    char *src = "testest";

    status = gmem_init(gourp_id);
    if (status != GMEM_SUCCESS) {
        return 0;
    }

    printf("%s\n", string_of_memtype(gmem_get_memory_type()));

    printf("hello from gucxt_info\n");

    
    gmem_alloc(&p, 100);
    gmem_memcpy(p, src, strlen(src));
    printf("%s\n", (char*)p);
}