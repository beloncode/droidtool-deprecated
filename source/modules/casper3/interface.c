#include "interface.h"

static module_t module_info;

__attribute__((unused)) module_t* casper3_init(backend_ctx_t* module_backend) {
    return &module_info;
}

static module_t module_info = {
    .module_name = "Casper3",
    .module_version = "0.0.1a0"
};

