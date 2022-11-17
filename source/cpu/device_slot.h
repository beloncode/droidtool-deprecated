
#ifndef CPU_DEVICE_SLOT_H
#define CPU_DEVICE_SLOT_H

#include "common/types.h"
#include "collect/bitmap.h"

typedef enum { CPU_VENDOR_INVALID, CPU_VENDOR_AMD } cpu_vendor_e;

typedef struct {
    char* vendor_string;
    cpu_vendor_e vendor_id;
    u8 max_parameter;

    u32* cpuid_saved_ctx;
    bitmap_coll_t* cpu_flags_map;

} cpu_device_t;

#endif
