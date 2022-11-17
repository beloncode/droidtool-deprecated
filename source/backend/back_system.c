#include "back_system.h"

static i32 backend_load_modules(droidtool_ctx_t* droidtool_ctx) {
    (void)droidtool_ctx;
    return 0;
}

static i32 backend_unload_modules(droidtool_ctx_t* droidtool_ctx) {
    (void)droidtool_ctx;
    return 0;
}

i32 backend_init(droidtool_ctx_t* droidtool_ctx) {
    backend_load_modules(droidtool_ctx);
    return 0;
}

i32 backend_deinit(droidtool_ctx_t* droidtool_ctx) {
    backend_unload_modules(droidtool_ctx);
    return 0;
}
