#include <malloc.h>

#include "manager_wrap.h"

void* dt_calloc(u32 elements_count, u32 element_size) {

    if (elements_count == 0 || element_size == 0) return NULL;
    u64 check_overflow = elements_count * element_size;
    if (check_overflow / elements_count != element_size) return NULL;

    void* new_ptr = calloc(elements_count, element_size);

    return new_ptr;
}

void dt_free(void* delete) {
    free(delete);
}
