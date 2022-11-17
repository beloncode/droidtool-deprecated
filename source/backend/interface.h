
#ifndef BACKEND_INTERFACE_H
#define BACKEND_INTERFACE_H

#include "backend_comm.h"

// Every module must implement this function
__attribute__((unused)) typedef module_t* (*module_init)(backend_ctx_t* module_backend);

#endif
