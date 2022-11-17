

#ifndef PLATFORM_NON_ANSI_H
#define PLATFORM_NON_ANSI_H

#include <stdarg.h>

#include "common/types.h"

i32 non_ansi_asprintf(char **restrict strp, const char *restrict fmt, ...);
i32 non_ansi_vasprintf(char **restrict strp, const char *restrict fmt, va_list ap);

#endif
