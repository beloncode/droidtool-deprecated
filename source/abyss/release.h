
#ifndef EVENT_RELEASE_H
#define EVENT_RELEASE_H

#include "log.h"

#define abyss_procedure(level, context, fmt, ...) \
    do {\
        abyss_source_t stack_source = {\
            .log_line = __LINE__, .log_filename = __FILE__\
        };\
        abyss_release(&stack_source, level, context, fmt, ##__VA_ARGS__);                          \
    } while(0)
#endif

#define abyss_error(context, fmt, ...) \
    abyss_procedure(ABYSS_LEVEL_ERROR, context, fmt, ##__VA_ARGS__)
