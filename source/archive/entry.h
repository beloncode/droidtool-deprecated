#ifndef ARCHIVE_ENTRY_H
#define ARCHIVE_ENTRY_H

#include <fcntl.h>

#include "common/types.h"

typedef enum {
    AERR_INV_PARAMS,
    AERR_ALREADY_OPENED,
    // AERR_CANT_OPEN_DIR,
    // AERR_CANT_OPEN_FILE,
    AERR_IS_FINE
} archive_err_e;

typedef enum {
    AM_INVALID_ONE = 0,
    AM_DIRECTORY = 1,
    AM_READ = 1 << 2,
    AM_WRITE = 1 << 3,
    AM_RW_APPEND = 1 << 4,
    AM_RW_TRUNCATE = 1 << 5
} archive_mode_e;

typedef struct {

    const char* dir_name;

    const char* absolute_path;

    i32 dir_mode;

    i32 dir_native_mode;

    i32 native_fd;

} archive_dir_t;

/*
typedef struct {
} archive_file_t;
*/

#endif
