#include "WinnerVisualiser.h"

#include <gb/gb.h>

static void draw_winner(void) {
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
    set_win_tiles(5, 3, 10, 1, "YOU WINNER");
    scroll_win(0, -24);
    u8 coolSmile[] = {20, 21};
    set_win_tiles(9, 0, 2, 1, coolSmile);
}

const struct WinnerVisualiserClass WinnerVisualiser = {

    .draw_winner = draw_winner,

};