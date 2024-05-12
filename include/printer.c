#include "printer.h"

#include <gb/gb.h>

void win_num_print(u8 x, u8 y, u8 num) {
    u8 _1000 = num / 1000;
    u8 _100 = (num % 1000) / 100;
    u8 _10 = (num % 100) / 10;
    u8 _1 = num % 10;
    u8 nums[] = {
        17 + _1000,
        17 + _100,
        17 + _10,
        17 + _1,
    };
    set_win_tiles(x, y, 4, 1, nums);
}