#ifndef ARCHIVE_DIRECTORY_H
#define ARCHIVE_DIRECTORY_H

#include "context.h"
#include "entry.h"

archive_err_e archive_opendir(const char* dir_filename, const char* dir_mode,
                              archive_dir_t* output_dir, archive_dir_t* parent_dir,
                              droidtool_ctx_t* droidtool_ctx);

archive_err_e archive_closedir(archive_dir_t* close_dir, droidtool_ctx_t* droidtool_ctx);

#endif
