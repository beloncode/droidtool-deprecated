#include <ctype.h>
#include <sys/stat.h>

#include "abyss/release.h"
#include "entries_check.h"
#include "entry.h"

i32 archive_mode_from_string(const char* mode_string,
                                        droidtool_ctx_t* droidtool_ctx) {
    i32 mode_flags = AM_INVALID_ONE;
    if (*mode_string == '\0') return mode_flags;
    // Permissions are even be at end of the permission string
    if (isdigit(*mode_string)) return mode_flags;

    while (*mode_string != '\0' && *mode_string != ':' && isalnum(*mode_string))
    {
        switch (*mode_string)
        {
            case 'd': mode_flags |= AM_DIRECTORY; break;
            case 'r': mode_flags |= AM_READ; break;
            case 'w': mode_flags |= AM_WRITE; break;
            case 'a': mode_flags |= AM_RW_APPEND; break;
            case '*': mode_flags |= AM_RW_TRUNCATE; break;
            default:
                abyss_error(droidtool_ctx, "%c not a valid mode, going out\n", *mode_string);
                return mode_flags;
        }
        mode_string++;
    }
    return mode_flags;
}

// Checks if something with 'real_filename' exist
// Filename is relative or an absolute filename, this depends on who is called him!
// Hard or Soft links aren't allowed!
bool archive_exist(const char* real_filename, droidtool_ctx_t* droidtool_ctx) {
    struct stat unix_stat;
    if (stat(real_filename, &unix_stat) != 0)
    {
        abyss_error(droidtool_ctx, "%s doesn't exist inside the virtual file system!",
                    real_filename);
        return false;
    }

    return S_ISDIR(unix_stat.st_mode) && (!S_ISLNK(unix_stat.st_mode));
}

i32 archive_mode_to_native(i32 archive_mode) {
    i32 native_mode = 0;

    if (archive_mode & AM_DIRECTORY) native_mode |= O_DIRECTORY;
    if (archive_mode & AM_READ) native_mode |= O_RDONLY;
    if (archive_mode & AM_WRITE) native_mode |= O_RDWR;
    if (archive_mode & AM_RW_APPEND) native_mode |= O_APPEND;
    if (archive_mode & AM_RW_TRUNCATE) native_mode |= O_TRUNC;

    return native_mode;
}