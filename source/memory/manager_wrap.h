
#ifndef MEMORY_MGR_H
#define MEMORY_MGR_H

#include "common/types.h"

void* dt_calloc(u32 elements_count, u32 element_size);
void dt_free(void* delete);

#endif
