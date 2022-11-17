
#ifndef BACKEND_BACKEND_COMM_H
#define BACKEND_BACKEND_COMM_H

#include "module.h"
#include "collect/doubly.h"

__attribute__((unused)) typedef struct {
    module_t* lib_module;

} module_ctx_t;

// Where's external modules with communicate to for access the droidtool components like
// log system, cache system, thread pool and others!
typedef struct {
    doubly_coll_t* modules_list;
} backend_ctx_t;

#endif