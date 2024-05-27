#include "GOVisualiser.h"

#include <gb/gb.h>

static void draw_gameover(void) {
    u8 window0[] = {
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  // 0
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  // 0
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  // 1
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  // 1
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  // 2
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  // 2
    };
    u8 window1[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 1
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 1
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 2
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 2
    };
    VBK_REG = VBK_BANK_1;
    set_win_tiles(0, 2, 20, 3, window1);
    VBK_REG = VBK_BANK_0;
    set_win_tiles(0, 2, 20, 3, window0);
    set_win_tiles(6, 3, 8, 1, "GAMEOVER");
    scroll_win(0, -24);
}

const struct GOVisualiserClass GOVisualiser = {

    .draw_gameover = draw_gameover,

};