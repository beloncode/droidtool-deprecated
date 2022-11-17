#include <unistd.h>

#include "memory/manager_wrap.h"
#include "abyss/release.h"
#include "entries_check.h"
#include "directory.h"

archive_err_e archive_opendir(const char* dir_filename, const char* dir_mode,
                    archive_dir_t* output_dir, archive_dir_t* parent_dir,
                    droidtool_ctx_t* droidtool_ctx) {
    if (*dir_filename == '\0') return AERR_INV_PARAMS;

    (void)parent_dir;
    output_dir->dir_mode = archive_mode_from_string(dir_mode, droidtool_ctx);
    const bool archive_test = archive_exist(dir_filename, droidtool_ctx);

    if (archive_test != true) return AERR_ALREADY_OPENED;

    output_dir->dir_native_mode = archive_mode_to_native(output_dir->dir_mode);

    return AERR_IS_FINE;
}

archive_err_e archive_closedir(archive_dir_t* close_dir, droidtool_ctx_t* droidtool_ctx) {
    if (close_dir->native_fd < 1)
    {
        const char* directory_name = "(Invalid directory)";

        if (close_dir->dir_name != NULL) directory_name = close_dir->dir_name;

        abyss_error(droidtool_ctx, "Directory %s hasn't be opened!", directory_name);

        return AERR_INV_PARAMS;
    }

    close(close_dir->native_fd);
    dt_free((void*)close_dir->dir_name);

    return AERR_IS_FINE;
}
