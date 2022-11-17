#ifndef ARCHIVE_ENTRIES_CHECK_H
#define ARCHIVE_ENTRIES_CHECK_H

#include "context.h"

i32 archive_mode_from_string(const char* mode_string,
                                        droidtool_ctx_t* droidtool_ctx);

bool archive_exist(const char* real_filename, droidtool_ctx_t* droidtool_ctx);

i32 archive_mode_to_native(i32 archive_mode);

#endif
