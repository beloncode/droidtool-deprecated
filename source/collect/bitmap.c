#include <string.h>

#include "bitmap_access.h"
#include "abyss/release.h"

i32 bitmap_init(u8* map_address, u64 map_size, u64 level_bound,
                bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    bitmap_ctx->map_address = map_address;
    bitmap_ctx->map_size = map_size;
    bitmap_ctx->level_bound = level_bound;

    if (level_bound == 0)
    {
        abyss_error(droidtool_ctx, "One or more level configurations is 0!\n");
    }

    bitmap_ctx->level_count = map_size / level_bound;

    return 0;
}

static i32 bitmap_check_page(u8* map_address, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    if (bitmap_ctx->map_address == map_address) return true;
    if (bitmap_ctx->map_address < map_address + bitmap_ctx->map_size) return true;

    abyss_error(droidtool_ctx, "Map address (%s) out of scope\n", map_address);

    return false;
}


__attribute__((unused)) i32 bitmap_copy(u8* map_out, u64 out_size, u64 map_start, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    u8* copy_location = bitmap_ctx->map_address + bitmap_ctx->level_bound * map_start;

    if (bitmap_check_page(copy_location, bitmap_ctx, droidtool_ctx) == false) return -1;

    u8* final_address = copy_location + out_size;

    if (bitmap_check_page(final_address, bitmap_ctx, droidtool_ctx) == false)
    {
        abyss_error(droidtool_ctx, "Final address isn't accessible for perform a copy %p", final_address);
        return -1;
    }

    return memcpy(map_out, copy_location, out_size) != NULL;
}

u8 bitmap_apply_mask(mask_method_e method, u8 mask, u64 start_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    u8* map_mask = bitmap_ctx->map_address + start_page * bitmap_ctx->level_bound;

    if (bitmap_check_page(map_mask, bitmap_ctx, droidtool_ctx) == false)
    {
        abyss_error(droidtool_ctx, "Map address %p is out of bounding\n", map_mask);
        return false;
    }

    u8 mask_result = 0;

    switch(method)
    {
    case MASK_AND:
        mask_result = *map_mask &= mask; break;
    case MASK_OR:
        mask_result = *map_mask |= mask; break;
    case MASK_XOR:
        mask_result = *map_mask ^= mask; break;
    default:
        abyss_error(droidtool_ctx, "Invalid method of number %d\n", method);
    }
    return mask_result;
}

__attribute__((unused)) bool bitmap_clear(u64 start_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    return bitmap_apply_mask(MASK_AND, 0x0, start_page, bitmap_ctx, droidtool_ctx) == 0;
}

i32 bitmap_test_mask(u8 mask, u8 mask_range, u64 start_page, bitmap_coll_t* bitmap_ctx,
                         droidtool_ctx_t* droidtool_ctx) {
    if (mask_range > 7)
    {
        abyss_error(droidtool_ctx, "Mask range couldn't be bigger than a byte size in bits");
        return 0;
    }

    u8* map_bitcheck = bitmap_ctx->map_address + start_page * bitmap_ctx->level_bound;

    if (bitmap_check_page(map_bitcheck, bitmap_ctx, droidtool_ctx) == false) return 0;

    if (mask_range != 0)
    {
        // Mask it's positioned inside 2 bytes pages
        u8 first_byte = *map_bitcheck++;

        if (bitmap_check_page(map_bitcheck, bitmap_ctx, droidtool_ctx) == false) return 0;

        u8 second_byte = *map_bitcheck;
        u8 remain_bit_position = 8 - mask_range;
        u8 final_byte = first_byte>>mask_range;
        final_byte |= second_byte>>remain_bit_position;
        return final_byte;

    }

    return mask & *map_bitcheck;

}

__attribute__((unused)) bool bitmap_compare_mask(u8 mask, u8 mask_range, u64 start_page, bitmap_coll_t* bitmap_ctx,
                        droidtool_ctx_t* droidtool_ctx) {

    return bitmap_test_mask(mask, mask_range, start_page, bitmap_ctx, droidtool_ctx) == mask;
}

i32 bitmap_check(i32 bit_position, u64 level_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    if (level_page > bitmap_ctx->level_count)
    {
        abyss_error(droidtool_ctx, "%ld is bigger than the actual level count %ld\n",
                    level_page, bitmap_ctx->level_count);
        return -1;
    }
    u8* map_search = bitmap_ctx->map_address + bitmap_ctx->level_bound * level_page;

    while (bit_position % 8 != 0)
    {
        map_search++;
        bit_position-=8;
    }

    if (bitmap_check_page(map_search, bitmap_ctx, droidtool_ctx) != 0)
    {
        abyss_error(droidtool_ctx, "%p address is out of bounding of the bitmap map address\n",
                    level_page, bitmap_ctx->level_count);
        return -1;
    }

    return *map_search >> bit_position;
}

__attribute__((unused)) bool bitmap_is_set(i32 bit_position, u64 level_page, bitmap_coll_t* bitmap_ctx, droidtool_ctx_t* droidtool_ctx) {
    i32 bitmap_ret;

    if ((bitmap_ret = bitmap_check(bit_position, level_page, bitmap_ctx, droidtool_ctx)) != -1) {
        return bitmap_ret;
    }

    return false;
}

i32 bitmap_deinit(bitmap_coll_t* bitmap_ctx) {
    explicit_bzero(bitmap_ctx->map_address, bitmap_ctx->map_size);
    explicit_bzero(bitmap_ctx, sizeof(*bitmap_ctx));
    return 0;
}

