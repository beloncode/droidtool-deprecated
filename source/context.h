#ifndef CONTEXT_H
#define CONTEXT_H

#include "archive/entry.h"
#include "abyss/event.h"
#include "cpu/device_slot.h"
#include "backend/backend_comm.h"
#include "user.h"

typedef struct {

    archive_dir_t* process_working_dir;

} process_ctx_t;

typedef struct {

    user_options_t* user_options;

    cpu_device_t* cpu_device;

    abyss_log_t* log_system_t;

    process_ctx_t* process_ctx;

    backend_ctx_t* backend_ctx;

} droidtool_ctx_t;

i32 droidtool_init(droidtool_ctx_t* droidtool_ctx);
i32 droidtool_deinit(droidtool_ctx_t* droidtool_ctx);

#endif
