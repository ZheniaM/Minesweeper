#include <gb/cgb.h>
#include <gb/gb.h>
#include <time.h>

#include "classes/Game/GameLogic.h"
#include "classes/GameOver/GOLogic.h"
#include "classes/Logic.h"
#include "classes/Title/TitleLogic.h"
#include "classes/Winner/WinnerLogic.h"
#include "data/bkg.h"
#include "data/cursores.h"
#include "include/short_types.h"

clock_t get_time(void) { return clock() / 4; }

u8 do_nothing(void) { return 0; }

void init(void) {
    const palette_color_t bkgPalette[] = {
        bkgTilesCGBPal0c0, bkgTilesCGBPal0c1, bkgTilesCGBPal0c2,
        bkgTilesCGBPal0c3, bkgTilesCGBPal1c0, bkgTilesCGBPal1c1,
        bkgTilesCGBPal1c2, bkgTilesCGBPal1c3, bkgTilesCGBPal2c0,
        bkgTilesCGBPal2c1, bkgTilesCGBPal2c2, bkgTilesCGBPal2c3,
        bkgTilesCGBPal3c0, bkgTilesCGBPal3c1, bkgTilesCGBPal3c2,
        bkgTilesCGBPal3c3, bkgTilesCGBPal4c0, bkgTilesCGBPal4c1,
        bkgTilesCGBPal4c2, bkgTilesCGBPal4c3, bkgTilesCGBPal5c0,
        bkgTilesCGBPal5c1, bkgTilesCGBPal5c2, bkgTilesCGBPal5c3,
        bkgTilesCGBPal6c0, bkgTilesCGBPal6c1, bkgTilesCGBPal6c2,
        bkgTilesCGBPal6c3, bkgTilesCGBPal7c0, bkgTilesCGBPal7c1,
        bkgTilesCGBPal7c2, bkgTilesCGBPal7c3,
    };

    palette_color_t cPalette[] = {
        cursoreDataCGBPal0c0,
        cursoreDataCGBPal0c1,
        cursoreDataCGBPal0c2,
        cursoreDataCGBPal0c3,
    };

    set_bkg_palette(0, 8, &bkgPalette[0]);
    set_bkg_data(0, 92, bkgTiles);
    set_sprite_palette(0, 8, cPalette);
    set_sprite_data(0, 3, cursoreData);
}

int main(void) {
    if (CGB_TYPE == _cpu) {
        cpu_fast();
    }
    init();

    SHOW_WIN;
    TitleLogic.start();
    // GameLogic.start(8, 8, 10);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    clock_t frame = get_time();
    Logic *l = TitleLogic.logic;
    while (TRUE) {
        if (get_time() == frame) {
            continue;
        }
        wait_vbl_done();
        u8 next = l->make_cycle();
        switch (next) {
            case IDLE_SCENE:
                break;

            case GAME_SCENE:
                DISPLAY_OFF;
                l->delete ();
                l = GameLogic.logic;
                GameLogic.start();  // (8, 8, 10);
                DISPLAY_ON;
                break;

            case END_SCENE:
                DISPLAY_OFF;
                l->delete ();
                l = WinnerLogic.logic;
                WinnerLogic.start();
                DISPLAY_ON;
                break;

            case TITLE_SCENE:
                DISPLAY_OFF;
                l->delete ();
                l = TitleLogic.logic;
                TitleLogic.start();
                DISPLAY_ON;
                break;

            case GAMEOVER_SCENE:
                DISPLAY_OFF;
                l->delete ();
                l = GOLogic.logic;
                GOLogic.start();
                DISPLAY_ON;
                break;
        }
        frame = get_time();
    }
}