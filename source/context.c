#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "memory/manager_wrap.h"
#include "abyss/release.h"
#include "platform/non_ansi.h"
#include "context.h"
#include "cpu/device.h"
#include "archive/directory.h"
#include "backend/back_system.h"

char* fetch_absolute_rundir(char* output_buffer, u64 buffer_sz, droidtool_ctx_t* droidtool_ctx) {
    #define USER_SELF_INSTEAD 0
    char* exe_virtual = NULL;
    #if USER_SELF_INSTEAD
    #else
    non_ansi_asprintf(&exe_virtual, "/proc/%d/exe", getpid());

    const u64 link_ret = (u64)readlink(exe_virtual, output_buffer, buffer_sz);

    dt_free(exe_virtual);

    if (link_ret == -1)
    {
        char errno_buffer[0x38];
        strerror_r(errno, errno_buffer, sizeof(errno_buffer));

        abyss_error(droidtool_ctx, "Can't read information from %s, because %s\n",
                    exe_virtual, errno_buffer);
        return NULL;
    }

    char* delimiter_exe;
    if ((delimiter_exe = strrchr(output_buffer, '/'))) *delimiter_exe = '\0';

    #endif

    return output_buffer;
}

i32 process_init(droidtool_ctx_t* droidtool_ctx) {
    process_ctx_t* process_context = droidtool_ctx->process_ctx;

    #define WORKING_DIR_SZ 0x145
    static char working_directory[WORKING_DIR_SZ];

    fetch_absolute_rundir(working_directory, sizeof(working_directory), droidtool_ctx);

    process_context->process_working_dir = (archive_dir_t*)dt_calloc(1, sizeof(archive_dir_t));

    const archive_err_e arch_error = archive_opendir(working_directory, "drw",
                                                     process_context->process_working_dir,
                                                     NULL, droidtool_ctx);
    if (arch_error != AERR_IS_FINE) {}

    return 0;
}

i32 process_deinit(droidtool_ctx_t* droidtool_ctx) {
    process_ctx_t* process_context = droidtool_ctx->process_ctx;
    archive_dir_t* working_dir = process_context->process_working_dir;

    archive_closedir(working_dir, droidtool_ctx);

    dt_free(working_dir);

    return 0;
}

i32 droidtool_init(droidtool_ctx_t* droidtool_ctx) {
    droidtool_ctx->cpu_device = (cpu_device_t*)dt_calloc(1, sizeof(cpu_device_t));
    droidtool_ctx->log_system_t = (abyss_log_t*)dt_calloc(1, sizeof(abyss_log_t));
    droidtool_ctx->user_options = (user_options_t*)dt_calloc(1, sizeof(user_options_t));
    droidtool_ctx->process_ctx = (process_ctx_t*)dt_calloc(1, sizeof(process_ctx_t));
    droidtool_ctx->backend_ctx = (backend_ctx_t*)dt_calloc(1, sizeof(backend_ctx_t));

    cpu_init(droidtool_ctx);
    process_init(droidtool_ctx);
    backend_init(droidtool_ctx);

    return 0;

}
i32 droidtool_deinit(droidtool_ctx_t* droidtool_ctx) {
    cpu_deinit(droidtool_ctx);
    process_deinit(droidtool_ctx);
    backend_deinit(droidtool_ctx);

    dt_free(droidtool_ctx->user_options);
    dt_free(droidtool_ctx->log_system_t);
    dt_free(droidtool_ctx->cpu_device);
    dt_free(droidtool_ctx->process_ctx);
    dt_free(droidtool_ctx->backend_ctx);

    return 0;
}

