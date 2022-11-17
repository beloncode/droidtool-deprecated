
#ifndef COLLECT_BITMAP_H
#define COLLECT_BITMAP_H

#include <stdbool.h>

#include "common/types.h"

typedef enum { MASK_AND, MASK_OR, MASK_XOR } mask_method_e;

typedef struct bitmap_coll {
    u8* map_address;
    u64 map_size;
    u64 level_bound;
    u64 level_count;

} bitmap_coll_t;

#endif
