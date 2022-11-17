
#ifndef COLLECT_BITMAP_ACCESS_H
#define COLLECT_BITMAP_ACCESS_H

#include "context.h"
#include "bitmap.h"

i32 bitmap_init(u8* map_address, u64 map_size, u64 level_bound,
                bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

static i32 bitmap_check_page(u8* map_address, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

__attribute__((unused)) i32 bitmap_copy(u8* map_out, u64 out_size, u64 map_start, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

u8 bitmap_apply_mask(mask_method_e method, u8 mask, u64 start_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

__attribute__((unused)) bool bitmap_clear(u64 start_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

i32 bitmap_test_mask(u8 mask, u8 mask_range, u64 start_page, bitmap_coll_t* bitmap_ctx,
                     droidtool_ctx_t* droidtool_ctx);

__attribute__((unused)) bool bitmap_compare_mask(u8 mask, u8 mask_range, u64 start_page, bitmap_coll_t* bitmap_ctx,
                         droidtool_ctx_t* droidtool_ctx);

i32 bitmap_check(i32 bit_position, u64 level_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

__attribute__((unused)) bool bitmap_is_set(i32 bit_position, u64 level_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx);

i32 bitmap_deinit(bitmap_coll_t* bitmap_ctx);


#endif
