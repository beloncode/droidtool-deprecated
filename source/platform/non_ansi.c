#include <stdio_ext.h>

#include "memory/manager_wrap.h"
#include "non_ansi.h"

i32 non_ansi_asprintf(char **restrict strp, const char *restrict fmt, ...) {
    va_list arg_array;
    va_start(arg_array, fmt);

    const i32 va_ret = non_ansi_vasprintf(strp, fmt, arg_array);

    va_end(arg_array);

    return va_ret;
}

i32 non_ansi_vasprintf(char **restrict strp, const char *restrict fmt, va_list ap) {
    va_list va_backup;
    va_copy(va_backup, ap);

    // vsprintf and others similar functions, destroy the va_list by consume it!
    const i32 needed_size = vsnprintf(NULL, 0, fmt, ap) + 0x1;

    *strp = dt_calloc(sizeof(char), needed_size);

    if (*strp == NULL) return -1;

    const i32 ansi_ret = vsnprintf(*strp, needed_size, fmt, va_backup);

    va_end(va_backup);
    return ansi_ret;
}
