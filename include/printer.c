#include "printer.h"

#include <gb/gb.h>

void win_num_print8(u8 x, u8 y, u8 num) {
    u8 nums[] = {
        55 + (num >> 4),
        55 + (num & 0x0fU),
    };
    set_win_tiles(x, y, 2, 1, nums);
}

void win_num_print16(u8 x, u8 y, u16 num) {
    u8 nums[] = {
        55 + ((num >> 12) & 0x000fU),
        55 + ((num >> 8) & 0x000fU),
        55 + ((num >> 4) & 0x000fU),
        55 + ((num >> 0) & 0x000fU),
    };
    set_win_tiles(x, y, 4, 1, nums);
}