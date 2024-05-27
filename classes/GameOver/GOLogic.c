#include "GOLogic.h"

#include "GOVisualiser.h"
static void start(void) { GOVisualiser.draw_gameover(); }

static u8 make_cycle(void) {
    if (joypad() == J_START) {
        return TITLE_SCENE;
    }
    return IDLE_SCENE;
}

static void delete(void) { return; }

static Logic l = {.make_cycle = make_cycle, .delete = delete};

struct GOLogicClass GOLogic = {

    .logic = &l,
    .start = start,

};