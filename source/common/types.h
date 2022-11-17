#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t u8;
typedef int32_t i32;
_Static_assert(sizeof(i32) == 4, "Integer type used into the system for represent a"
                                 " 4 bytes range value isn't a real 32bits integer,"
                                 " this incident must be reported!");
typedef uint32_t u32;

typedef uint64_t u64;
_Static_assert(sizeof(u64) == 8, "WTF!!!! Wait a minute...");

#endif

