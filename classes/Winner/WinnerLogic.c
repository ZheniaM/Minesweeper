#include "WinnerLogic.h"

#include "WinnerVisualiser.h"

static s8 dh = 0;

static void start(void) {
    WinnerVisualiser.draw_winner();
    dh = 24;
}

static u8 make_cycle(void) {
    switch (joypad()) {
        case J_START:
            return TITLE_SCENE;
        case J_DOWN:
            dh++;
            if (dh > 24) {
                dh = 24;
            } else {
                scroll_bkg(0, -1);
            }
            break;
        case J_UP:
            dh--;
            if (dh < 0) {
                dh = 0;
            } else {
                scroll_bkg(0, 1);
            }
            break;
    }
    return IDLE_SCENE;
}

static void delete(void) { return; }

static Logic l = {.make_cycle = make_cycle, .delete = delete};

struct WinnerLogicClass WinnerLogic = {

    .logic = &l,
    .start = start,

};