#include "TitleLogic.h"

#include <gb/gb.h>
#include <stdlib.h>

#include "../container.h"
#include "TitleVisualiser.h"

#define RISES 1
#define ON_H 2
#define ON_W 3
#define ON_MINES 4
#define ON_START 5
#define START_PRESSED 6

#define MAX_W 20
#define MAX_H 16

typedef struct {
    u8 w;
    u8 h;
    u8 numMines;
    u8 state;
    u8 win_level;
} TitleState;

TitleState *ts;

void start(void) {
    ts = malloc(sizeof(TitleState));
    ts->h = 8;
    ts->w = 8;
    ts->numMines = 10;
    ts->state = RISES;
    ts->win_level = 144;

    TitleVisualiser.init();
}

u8 rise(void) {
    if (joypad() == J_START) {
        ts->win_level = 1;
    }
    ts->win_level--;
    TitleVisualiser.move_win(ts->win_level);
    if (0 == ts->win_level) {
        return ON_H;
    }
    return RISES;
}

void init_container(void) {
    container.h = ts->h;
    container.w = ts->w;
    container.mines = ts->numMines;
}

u8 on_h(void) {
    switch (joypad()) {
        case J_RIGHT:
            ts->h += 2;
        case J_LEFT:
            ts->h--;
            if (ts->h < 4) ts->h = 4;
            if (ts->h > MAX_H) ts->h = MAX_H;
            return ON_H;
        case J_UP:
            return ON_START;
        case J_DOWN:
            return ON_W;
        case J_START:
            return START_PRESSED;
    }
    return ON_H;
}

u8 on_w(void) {
    switch (joypad()) {
        case J_RIGHT:
            ts->w += 2;
        case J_LEFT:
            ts->w--;
            if (ts->w > MAX_W) ts->w = MAX_W;
            if (ts->w < 4) ts->w = 4;
            return ON_W;
        case J_UP:
            return ON_H;
        case J_DOWN:
            return ON_MINES;
        case J_START:
            return START_PRESSED;
    }
    return ON_W;
}

u8 on_mines(void) {
    switch (joypad()) {
        case J_RIGHT:
            ts->numMines += 1;
            if (ts->numMines < 1) ts->numMines = 1;
            return ON_MINES;
        case J_LEFT:
            ts->numMines -= 1;
            if (ts->numMines < 1) ts->numMines = 1;
            return ON_MINES;
        case J_UP:
            return ON_W;
        case J_DOWN:
            return ON_START;
        case J_START:
            return START_PRESSED;
    }
    return ON_MINES;
}

u8 on_start(void) {
    switch (joypad()) {
        case J_A:
        case J_START:
            return START_PRESSED;
        case J_UP:
            return ON_MINES;
        case J_DOWN:
            return ON_H;
    }
    return ON_START;
}

u8 make_cucle(void) {
    TitleVisualiser.print_nums(ts->h, ts->w, ts->numMines);
    switch (ts->state) {
        case RISES:
            ts->state = rise();
            break;
        case ON_H:
            TitleVisualiser.draw_active_h();
            ts->state = on_h();
            break;
        case ON_W:
            TitleVisualiser.draw_active_w();
            ts->state = on_w();
            break;
        case ON_MINES:
            TitleVisualiser.draw_active_mines();
            ts->state = on_mines();
            break;
        case ON_START:
            TitleVisualiser.draw_active_start();
            ts->state = on_start();
            break;
        case START_PRESSED:
            TitleVisualiser.draw_no_active();
            init_container();
            return GAME_SCENE;
    }
    return IDLE_SCENE;
}

void delete(void) { return; }

static Logic l = {.make_cycle = make_cucle, .delete = delete};

struct TitleLogicClass TitleLogic = {
    .logic = &l,
    .start = start,
};