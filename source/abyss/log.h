#ifndef DROIDTOOL_EXECEV_H
#define DROIDTOOL_EXECEV_H

#include "context.h"
#include "common/types.h"

typedef enum { ABYSS_LEVEL_ERROR __attribute__((unused))} abyss_level_e;

typedef struct {
    i32 log_line;
    const char* log_filename;
} abyss_source_t;

i32 abyss_release(const abyss_source_t* source_location, abyss_level_e re_level,
                  droidtool_ctx_t* droidtool_ctx, const char* restrict fmt, ...);

__attribute__((unused)) i32 abyss_async(const abyss_source_t* source_location, abyss_level_e async_level,
                                        droidtool_ctx_t* droidtool_ctx, const char* restrict fmt, ...);

__attribute__((unused)) i32 abyss_async_time(u64 nano_sleep, const abyss_source_t* source_location,
                                             abyss_level_e async_le, droidtool_ctx_t* droidtool_ctx,
                                             const char* restrict fmt, ...);

#endif
