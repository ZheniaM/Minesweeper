#include "TitleVisualiser.h"

#include <gb/gb.h>

#include "../../data/TitleMap.h"
#include "../../include/printer.h"

static void init(void) {
    VBK_REG = VBK_BANK_1;
    set_win_tiles(0, 0, titleMapWidth, titleMapHeight, titleMapPLN1);
    VBK_REG = VBK_BANK_0;
    set_win_tiles(0, 0, titleMapWidth, titleMapHeight, titleMapPLN0);

    // set_sprite
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    move_win(7, 144);
}

static void _move_win(u8 y) { move_win(7, y); }

static void draw_active_h(void) {
    // move_sprite(0, 8 + 8, 16);
    move_sprite(1, 8 + 8 * 5, 16 + 8 * 4);
    move_sprite(2, 8 + 8 * 14, 16 + 8 * 4);
}

static void draw_active_w(void) {
    move_sprite(1, 8 + 8 * 5, 16 + 8 * 6);
    move_sprite(2, 8 + 8 * 14, 16 + 8 * 6);
}

static void draw_active_mines(void) {
    move_sprite(1, 8 + 8 * 5, 16 + 8 * 8);
    move_sprite(2, 8 + 8 * 14, 16 + 8 * 8);
}

static void draw_active_start(void) {
    move_sprite(1, 8 + 8 * 5, 16 + 8 * 10);
    move_sprite(2, 8 + 8 * 14, 16 + 8 * 10);
}

static void print_nums(u8 h, u8 w, u8 mines) {
    win_num_print8(12, 4, h);
    win_num_print8(12, 6, w);
    win_num_print8(12, 8, mines);
}

static void draw_no_active(void) {
    hide_sprite(1);
    hide_sprite(2);
}

const struct TitleVisualiserClass TitleVisualiser = {

    .init = init,
    .print_nums = print_nums,
    .move_win = _move_win,
    .draw_active_h = draw_active_h,
    .draw_active_w = draw_active_w,
    .draw_active_mines = draw_active_mines,
    .draw_active_start = draw_active_start,
    .draw_no_active = draw_no_active,

};