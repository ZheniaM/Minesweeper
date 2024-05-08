#include <gb/cgb.h>
#include <gb/gb.h>
#include <time.h>

#include "classes/Game/Cursor.h"
#include "classes/Game/DataPlane.h"
#include "classes/Game/GameLogic.h"
#include "classes/Game/GameVisualiser.h"
#include "data/bkg.h"
#include "data/bkgMap.h"
#include "include/short_types.h"

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

const u8 smile[] = {11, 12, 13, 14};
const u8 smileColors[] = {2, 2, 2, 2};

clock_t get_time(void) { return clock() / 5; }

int main(void) {
    if (CGB_TYPE == _cpu) {
        cpu_fast();
    }

    set_bkg_palette(0, 8, &bkgPalette[0]);
    set_bkg_data(0, 16, bkgTiles);
    // set map to video bank 1
    VBK_REG = VBK_BANK_1;
    set_bkg_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN1);
    set_win_tiles(9, 0, 2, 2, smileColors);
    // set map to video bank 0
    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN0);
    set_win_tiles(9, 0, 2, 2, smile);
    move_win(7, 128);

    // Cursor_t *cursor = Cursor.new(0, 0);
    // set_sprite_data(Cursor.get_nb(cursor), 1, Cursor.get_data(cursor));
    // set_sprite_palette(Cursor.get_palette_nb(cursor), 1,
    //                    Cursor.get_palette(cursor));
    // Cursor.move(cursor, 40, 80);
    Cursor.make(0, 0);
    set_sprite_data(Cursor.get_nb(), 1, Cursor.get_data());
    set_sprite_palette(Cursor.get_nb(), 1, Cursor.get_palette());
    Cursor.move(0, 0);
    move_sprite(Cursor.get_nb(), 8 + Cursor.get_x() * 8,
                16 + Cursor.get_y() * 8);

    DataPlane_t *plane = DataPlane.new(PS_10x10);
    GameVisualiser.draw_plane(plane);

    SHOW_SPRITES;
    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    clock_t frame = get_time();
    u8 dx = 0, dy = 0;
    while (TRUE) {
        if (get_time() == frame) {
            continue;
        }
        wait_vbl_done();
        dx = 0;
        dy = 0;
        switch (joypad()) {
            // case J_A:
            //     u8 x = Cursor.get_x(cursor);
            //     u8 y = Cursor.get_y(cursor);
            //     u8 cell = DataPlane.get_cell_state(plane, x, y);
            //     set_bkg_tile_xy(x, y, cell);
            case J_DOWN:
                dy += 1;
                break;
            case J_UP:
                dy -= 1;
                break;
            case J_LEFT:
                dx -= 1;
                break;
            case J_RIGHT:
                dx += 1;
                break;
        }
        if (dx || dy) {
            Cursor.scroll(dx, dy);
            move_sprite(Cursor.get_nb(), 8 + Cursor.get_x() * 8,
                        16 + Cursor.get_y() * 8);
        }
        // scroll_sprite(Cursor.get_nb(cursor), Cursor.get_x(cursor) * 8,
        //   Cursor.get_y(cursor) * 8);
        frame = get_time();
    }
}