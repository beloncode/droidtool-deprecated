#include <time.h>
#include <string.h>

#include "log.h"
#include "platform/non_ansi.h"
#include "memory/manager_wrap.h"

typedef enum {
    ABYSS_ASYNC_SLEEP
} abyss_async_e;

typedef struct {
    union {
        struct timespec sleep_time;
    };
    abyss_async_e async_type;
} message_async_t;

typedef struct {
    char* raw_message;
    abyss_source_t source_position;
    message_async_t message_async;
    abyss_level_e message_level;
} message_context_t;

static void abyss_gen_context(message_context_t* msg_ctx,
                              const abyss_source_t* source_location,
                              const abyss_level_e abyss_level,
                              message_async_t* abyss_async,
                              droidtool_ctx_t* droidtool_ctx,
                              const char* restrict fmt, va_list log_args) {
    user_options_t* user_options = droidtool_ctx->user_options;
    non_ansi_vasprintf(&msg_ctx->raw_message, fmt, log_args);

    if (user_options != NULL)
    {
        memcpy(&msg_ctx->source_position, source_location, sizeof(*source_location));
    }
    msg_ctx->message_level = abyss_level;

    if (abyss_async != NULL)
    {
        memcpy(&msg_ctx->message_async, abyss_async, sizeof(*abyss_async));
    }
}

i32 abyss_produce(message_context_t* message_ctx, droidtool_ctx_t* droidtool_ctx) {
    (void)droidtool_ctx;
    return (i32)strlen(message_ctx->raw_message);
}

i32 abyss_release(const abyss_source_t* source_location, abyss_level_e re_level,
                  droidtool_ctx_t* droidtool_ctx, const char* restrict fmt, ...) {
    va_list release_args;
    va_start(release_args, fmt);

    message_context_t message_ctx;
    abyss_gen_context(&message_ctx, source_location, re_level, NULL, droidtool_ctx, fmt,
                      release_args);

    va_end(release_args);

    const i32 prod_ret = abyss_produce(&message_ctx, droidtool_ctx);
    return prod_ret;
}

__attribute__((unused)) i32 abyss_async_va(const abyss_source_t* source_location, abyss_level_e async_level,
                message_async_t* async_way, droidtool_ctx_t* droidtool_ctx,
                const char* restrict fmt, va_list async_args) {

    message_context_t* message_heap = dt_calloc(1, sizeof(message_context_t));

    abyss_gen_context(message_heap, source_location, async_level, async_way,
                      droidtool_ctx, fmt, async_args);
    const i32 produce_ret = abyss_produce(message_heap, droidtool_ctx);

    return produce_ret;
}

__attribute__((unused)) i32 abyss_async_time(u64 nano_sleep, const abyss_source_t* source_location,
                                             abyss_level_e async_le, droidtool_ctx_t* droidtool_ctx,
                                             const char* restrict fmt, ...) {
    va_list async_args;
    va_start(async_args, fmt);

    message_async_t stack_async = {
        .async_type = ABYSS_ASYNC_SLEEP,
    };
    struct timespec sleep_time = { .tv_nsec = (long)nano_sleep };
    memcpy(&stack_async.sleep_time, &sleep_time, sizeof(sleep_time));

    const i32 async_ret = abyss_async_va(source_location, async_le, &stack_async,
                                         droidtool_ctx, fmt, async_args);
    va_end(async_args);
    return async_ret;
}
