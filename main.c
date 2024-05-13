#include <gb/cgb.h>
#include <gb/gb.h>
#include <time.h>

#include "include/short_types.h"
// #include "classes/Game/Cursor.h"
// #include "classes/Game/GameLogic.c"
#include "classes/Game/GameLogic.h"
// #include "classes/Game/GameVisualiser.h"
// #include "classes/Game/PlaneData.h"
// #include "classes/Game/PlaneFabric.h"
#include "data/bkg.h"
#include "data/bkgMap.h"

const palette_color_t bkgPalette[] = {
    bkgTilesCGBPal0c0, bkgTilesCGBPal0c1, bkgTilesCGBPal0c2, bkgTilesCGBPal0c3,
    bkgTilesCGBPal1c0, bkgTilesCGBPal1c1, bkgTilesCGBPal1c2, bkgTilesCGBPal1c3,
    bkgTilesCGBPal2c0, bkgTilesCGBPal2c1, bkgTilesCGBPal2c2, bkgTilesCGBPal2c3,
    bkgTilesCGBPal3c0, bkgTilesCGBPal3c1, bkgTilesCGBPal3c2, bkgTilesCGBPal3c3,
    bkgTilesCGBPal4c0, bkgTilesCGBPal4c1, bkgTilesCGBPal4c2, bkgTilesCGBPal4c3,
    bkgTilesCGBPal5c0, bkgTilesCGBPal5c1, bkgTilesCGBPal5c2, bkgTilesCGBPal5c3,
    bkgTilesCGBPal6c0, bkgTilesCGBPal6c1, bkgTilesCGBPal6c2, bkgTilesCGBPal6c3,
    bkgTilesCGBPal7c0, bkgTilesCGBPal7c1, bkgTilesCGBPal7c2, bkgTilesCGBPal7c3,
};

const u8 smile[] = {
    16, 16, 16, 16, 16, 16, 16, 16, 16, 11,  //
    12, 16, 16, 16, 16, 16, 16, 16, 16, 16,  //

    16, 16, 16, 16, 16, 16, 16, 16, 16, 13,  //
    14, 16, 16, 16, 16, 16, 16, 16, 16, 16,  //
};
const u8 smileColors[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
// const u8 smile[] = {11, 12, 13, 14};
// const u8 smileColors[] = {2, 2, 2, 2};
clock_t get_time(void) { return clock() / 4; }

int main(void) {
    if (CGB_TYPE == _cpu) {
        cpu_fast();
    }

    set_bkg_palette(0, 8, &bkgPalette[0]);
    set_bkg_data(0, 47, bkgTiles);
    // set map to video bank 1
    VBK_REG = VBK_BANK_1;
    // set_bkg_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN1);
    set_win_tiles(0, 0, 20, 2, smileColors);
    // set map to video bank 0
    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN0);
    set_win_tiles(0, 0, 20, 2, smile);
    move_win(7, 128);
    SHOW_WIN;
    GameLogic.make(8, 8, 10);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    clock_t frame = get_time();
    while (TRUE) {
        if (get_time() == frame) {
            continue;
        }
        wait_vbl_done();
        GameLogic.logic.make_cycle();
        frame = get_time();
    }
}