
#include "common/types.h"
#include "context.h"
#include "memory/manager_wrap.h"

i32 main() {

    droidtool_ctx_t* main_context = (droidtool_ctx_t*)dt_calloc(1, (u32)sizeof(*main_context));

    if (main_context == NULL) return -1;

    droidtool_init(main_context);

    droidtool_deinit(main_context);

    dt_free(main_context);

    return 0;
}
