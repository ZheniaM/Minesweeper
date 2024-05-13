#include "printer.h"

#include <gb/gb.h>

void win_num_print(u8 x, u8 y, u8 num) {
    u8 nums[] = {
        17 + (num >> 4),
        17 + (num & 0x0fU),
    };
    set_win_tiles(x, y, 2, 1, nums);
}