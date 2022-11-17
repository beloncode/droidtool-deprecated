#include <cpuid.h>
#include <stdbool.h>
#include <string.h>
#include <stdio_ext.h>

#include "collect/bitmap_access.h"
#include "abyss/release.h"
#include "device.h"
#include "platform/non_ansi.h"
#include "memory/manager_wrap.h"

static const u8 g_cpu_vendor_leaf = 0;

static i32 fetch_cpu_vendor_id(char* vendor_buffer, i32 vendor_sz) {
    static u32 vendor_name[4];

    const bool cpuid_ok = __get_cpuid(g_cpu_vendor_leaf,
                                      &vendor_name[0],
                                      &vendor_name[1],
                                      &vendor_name[2],
                                      &vendor_name[3]);
    // Vendor string is loaded into ebx, edx, and ecx (in this order)
    // we need to swap ecx with edx for get the correct vendor string id!
    u32 vendor_edx_mmove = vendor_name[2];
    vendor_name[2] = vendor_name[3];
    vendor_name[3] = vendor_edx_mmove;

    snprintf(vendor_buffer, vendor_sz, "%.12s", (char*)(vendor_name + 1));

    if (cpuid_ok != true) return -1;
    return (i32)__get_cpuid_max(g_cpu_vendor_leaf, NULL);
}

static const char* cpu_vendor_string[];

static cpu_vendor_e vendor_name_to_id(const char* vendor_name, droidtool_ctx_t* droidtool_ctx)
{
    const char* vendor_string = cpu_vendor_string[CPU_VENDOR_AMD];
    if (strncmp(vendor_name, vendor_string, strlen(vendor_string)) == 0) return CPU_VENDOR_AMD;

    abyss_error(droidtool_ctx, "Can't translate the CPU vendor name from %s to an recognized type!\n",
                vendor_name);

    return CPU_VENDOR_INVALID;
}

i32 cpu_init(droidtool_ctx_t* droidtool_ctx) {
    cpu_device_t* device_ctx = droidtool_ctx->cpu_device;

    char vendor_buffer[sizeof(i32) * 4];

    device_ctx->max_parameter = fetch_cpu_vendor_id(vendor_buffer, sizeof(vendor_buffer));
    if (device_ctx->max_parameter <= 0)
    {
        // Abyss isn't initialized yet, we need to display out this error to the std error only
        abyss_error(droidtool_ctx, "Can't fetch the CPU maximum identifier parameter!");
    }

    non_ansi_asprintf(&device_ctx->vendor_string, "%s", vendor_buffer);
    device_ctx->vendor_id = vendor_name_to_id(vendor_buffer, droidtool_ctx);

    device_ctx->cpu_flags_map = (bitmap_coll_t*)dt_calloc(1, sizeof(bitmap_coll_t));

    const u32 map_page = sizeof(i32) * 4;
    const u32 map_size = device_ctx->max_parameter * map_page;

    device_ctx->cpuid_saved_ctx = (u32*)dt_calloc(1, map_size);

    bitmap_init((u8*)device_ctx->cpuid_saved_ctx, map_size, map_page,
                device_ctx->cpu_flags_map, droidtool_ctx);

    return 0;
}
i32 cpu_deinit(droidtool_ctx_t* droidtool_ctx) {
    cpu_device_t* device_ctx = droidtool_ctx->cpu_device;

    if (device_ctx->vendor_string != NULL)
        dt_free(device_ctx->vendor_string);

    bitmap_deinit(device_ctx->cpu_flags_map);
    dt_free(device_ctx->cpu_flags_map);
    dt_free(device_ctx->cpuid_saved_ctx);

    return 0;
}

static const char* cpu_vendor_string[] = {
    "Invalid one, WTF!",
    "AuthenticAMD"
};
