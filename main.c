#include <gb/cgb.h>
#include <gb/gb.h>
#include <rand.h>
#include <time.h>

#include "classes/GameVisualiser.h"
#include "classes/Plane.h"
#include "data/bkg.h"
#include "data/bkgMap.h"
#include "data/cursores.h"
#include "include/BKG.h"
#include "include/OAM.h"
#include "include/Sprite.h"
#include "include/short_types.h"

const palette_color_t cursorePalette[] = {
    cursoreDataCGBPal0c0,
    cursoreDataCGBPal0c1,
    cursoreDataCGBPal0c2,
    cursoreDataCGBPal0c3,
};

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

clock_t get_time(void) { return clock() >> 2; }

#define w 10
#define h 10

// u8 plane[w * h] = {0};

// void gen_plane(u8 *plane) {}

int main(void) {
    if (CGB_TYPE == _cpu) {
        cpu_fast();
    }
    BKG.set_palette(0, 8, &bkgPalette[0]);
    BKG.set_data(0, 16, bkgTiles);
    // set map to video bank 1
    VBK_REG = VBK_BANK_1;
    BKG.set_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN1);
    // set map to video bank 0
    VBK_REG = VBK_BANK_0;
    BKG.set_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN0);

    OAM.set_data(0, 1, cursoreData);
    OAM.set_palette(0, 1, &cursorePalette[0]);

    Sprite_nb_t cursore = 0;
    Sprite.set_tile(cursore, 0);
    Sprite.move(cursore, 40, 8 * 10);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    // u8 t = TRUE;
    clock_t frame = get_time();
    u8 dx = 0, dy = 0;
    while (TRUE) {
        if (get_time() == frame) {
            continue;
        }
        wait_vbl_done();
        switch (joypad()) {
            case J_A:
                DataPlane_t *plane = DataPlane.new(PS_10x10);
                GameVisualiser.draw_plane(plane);
                DataPlane.delete(plane);
                break;
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
        Sprite.scroll(cursore, dx * 8, dy * 8);
        dx = 0;
        dy = 0;
        frame = get_time();
    }
}