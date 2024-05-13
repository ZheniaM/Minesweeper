#include "GameLogic.h"

#include <gb/cgb.h>
#include <gb/gb.h>

#include "../../include/printer.h"
#include "Cursor.h"
#include "GameEnums.h"
#include "GameVisualiser.h"
#include "PlaneData.h"
#include "PlaneFabric.h"

typedef struct GameLogic_t {
    u16 score;
    u8 mines_left;
    PlaneData_t *plane;
    Cursor_t *cursor;
} GameLogic_t;

GameLogic_t *gl;

static void make(u8 w, u8 h, u8 numOfMines) {
    gl = malloc(sizeof(GameLogic_t));
    gl->cursor = Cursor.new(0, 0);  // cursore;
    gl->plane = PlaneFabric.generate(w, h, numOfMines);
    gl->mines_left = PlaneData.get_mines(gl->plane);
    gl->score = 0;

    GameVisualiser.show_cursor(gl->cursor);
    GameVisualiser.draw_rect_of_blocks(w, 0, 32 - w, h);
    GameVisualiser.draw_rect_of_blocks(0, h, 32, 32 - h);
    GameVisualiser.draw_plane(gl->plane, 10, 0);
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

static u8 make_cycle(void) {
    u8 j = joypad();
    s8 dx = 0;
    s8 dy = 0;
    u8 x = Cursor.get_x(gl->cursor);
    u8 y = Cursor.get_y(gl->cursor);
    win_num_print(12, 0, x);
    win_num_print(12, 1, y);
    if (J_A == j) {
        if (PlaneData.clean_from_mine(gl->plane, x, y)) {
            reveal(x, y);
            return 0;
        }
        // GameVisualiser.draw_gameover();
        return 1;

    } else if (J_B == j) {
        if (PlaneData.set_flag(gl->plane, x, y)) {
            reveal(x, y);
            return 0;
        }
        // GameVisualiser.draw_nothing(x, y);
        return 0;
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
    return 0;
}

const struct GameLogicClass GameLogic = {

    .make = make,
    .delete = delete,
    .logic =
        {
            .make_cycle = make_cycle,
        },
};