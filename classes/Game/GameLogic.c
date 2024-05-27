#include "GameLogic.h"

#include <gb/cgb.h>
#include <gb/gb.h>

#include "../../data/bkg.h"
#include "../../data/bkgMap.h"
#include "../../include/printer.h"
#include "../container.h"
#include "../font.h"
#include "Cursor.h"
#include "GameEnums.h"
#include "GameVisualiser.h"
#include "PlaneData.h"
#include "PlaneFabric.h"

typedef struct GameLogic_t {
    u16 time;
    u8 mines_left;
    u8 size;
    u16 cleared_cells;
    PlaneData_t *plane;
    Cursor_t *cursor;
} GameLogic_t;

GameLogic_t *gl;

static void download_tiles(void) {
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

    // set map to video bank 1
    VBK_REG = VBK_BANK_1;
    // set_bkg_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN1);
    set_win_tiles(0, 0, 20, 2, smileColors);
    // set map to video bank 0
    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, 0, bkgMapWidth, bkgMapHeight, bkgMapPLN0);
    set_win_tiles(0, 0, 20, 2, smile);
    move_win(7, 128);

    u8 mines[] = "MINES";
    u8 time[] = "TIME";
    Inscription_t inscrs[] = {
        {.x = 0, .y = 0, .size = 4, .title = time},   //
        {.x = 0, .y = 1, .size = 5, .title = mines},  //
    };
    GameVisualiser.draw_inscriptions(2, inscrs);
}

static void start(void) {  //(u8 w, u8 h, u8 numOfMines) {
    download_tiles();
    u8 w = container.w;
    u8 h = container.h;
    u8 numOfMines = container.mines;
    GameVisualiser.centralize(h, w);
    gl = malloc(sizeof(GameLogic_t));
    gl->cursor = Cursor.new(0, 0);  // cursore;
    gl->plane = PlaneFabric.generate(w, h, numOfMines);
    gl->mines_left = PlaneData.get_mines(gl->plane);
    gl->cleared_cells = 0;
    gl->time = 0;
    gl->size = PlaneData.get_height(gl->plane) * PlaneData.get_width(gl->plane);

    GameVisualiser.show_cursor(gl->cursor);
    GameVisualiser.draw_rect_of_blocks(w, 0, 32 - w, h);
    GameVisualiser.draw_rect_of_blocks(0, h, 32, 32 - h);
    // GameVisualiser.draw_plane(gl->plane, 10, 0);
}

static void delete(void) {
    Cursor.delete(gl->cursor);
    PlaneData.delete(gl->plane);
    free(gl);
}

static u8 get_left_mines(void) { return gl->mines_left; }

static void reveal(u8 x, u8 y) {
    u8 cell = PlaneData.get_cell_state(gl->plane, x, y);
    GameVisualiser.draw_cell(cell, x, y);
}

void increment_time(void) {
    gl->time += 1;
    win_num_print16(5, 0, gl->time);
}

static u8 make_cycle(void) {
    increment_time();
    win_num_print8(6, 1, gl->mines_left);

    u8 v = 5;
    u16 r = v;
    for (u8 i = 1; i < v; i++) {
        r += (i << 1);
    }
    win_num_print8(14, 0, r);

    if (0 == gl->mines_left) {
        return END_SCENE;
    }

    u8 j = joypad();
    s8 dx = 0;
    s8 dy = 0;
    u8 x = Cursor.get_x(gl->cursor);
    u8 y = Cursor.get_y(gl->cursor);
    if (J_A == j) {
        if (PlaneData.clean_from_mine(gl->plane, x, y)) {
            gl->cleared_cells += 1;
            reveal(x, y);
            return IDLE_SCENE;
        }
        reveal(x, y);
        // GameVisualiser.draw_gameover();
        return GAMEOVER_SCENE;
    } else if (J_B == j) {
        if (PlaneData.set_flag(gl->plane, x, y)) {
            reveal(x, y);
            gl->mines_left -= 1;
        } else {
            GameVisualiser.draw_nothing(x, y);
            gl->mines_left += 1;
        }
        return IDLE_SCENE;
    }
    if (j & J_UP) {
        dy -= 1;
    }
    if (j & J_DOWN) {
        dy += 1;
    }
    if (j & J_LEFT) {
        dx -= 1;
    }
    if (j & J_RIGHT) {
        dx += 1;
    }
    GameVisualiser.scroll_cursor(gl->cursor, dx, dy,
                                 PlaneData.get_width(gl->plane),
                                 PlaneData.get_height(gl->plane));
    return IDLE_SCENE;
}

Logic l = {.make_cycle = make_cycle, .delete = delete};

struct GameLogicClass GameLogic = {
    .start = start,
    .logic = &l,
};
