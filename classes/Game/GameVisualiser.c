#include "GameVisualiser.h"

#include "../../include/printer.h"
// #include "__PlaneData.h"

static void set_mine(u8 x, u8 y) {
    VBK_REG = VBK_BANK_1;
    set_bkg_tile_xy(x, y, 2);
    VBK_REG = VBK_BANK_0;
    set_bkg_tile_xy(x, y, 10);
}

static void set_flag(u8 x, u8 y) {
    VBK_REG = VBK_BANK_1;
    set_bkg_tile_xy(x, y, 3);
    VBK_REG = VBK_BANK_0;
    set_bkg_tile_xy(x, y, 9);
}

static void set_number(u8 x, u8 y, u8 num) {
    VBK_REG = VBK_BANK_1;
    switch (num) {
        case 0:
            set_bkg_tile_xy(x, y, 0);
            break;
        case 1:
            set_bkg_tile_xy(x, y, 4);
            break;
        case 2:
            set_bkg_tile_xy(x, y, 5);
            break;
        case 3:
            set_bkg_tile_xy(x, y, 3);
            break;
        case 4:
            set_bkg_tile_xy(x, y, 4);
            break;
        case 5:
            set_bkg_tile_xy(x, y, 3);
            break;
        case 6:
            set_bkg_tile_xy(x, y, 3);
            break;
        case 7:
            set_bkg_tile_xy(x, y, 3);
            break;
        case 8:
            set_bkg_tile_xy(x, y, 5);
            break;
    }

    VBK_REG = VBK_BANK_0;
    set_bkg_tile_xy(x, y, num);
}

// static void draw_nothing(u8 x, u8 y) {
//     VBK_REG = VBK_BANK_1;
//     set_bkg_tile_xy(x, y, 0);
//     VBK_REG = VBK_BANK_0;
//     set_bkg_tile_xy(x, y, 0x0fU);
// }

static void draw_cell(u8 cell, u8 x, u8 y) {
    win_num_print(0, 1, cell);
    switch (cell & 0xf0U) {
        case 0:
            win_num_print(0, 0, 0);
            set_number(x, y, 0);
            break;

        case (CS_FLAG | 0000000 | 0000000000):
        case (CS_FLAG | CS_MINE | 0000000000):
        case (CS_FLAG | 0000000 | CS_VISIBLE):
        case (CS_FLAG | CS_MINE | CS_VISIBLE):
            win_num_print(0, 0, 1);
            set_number(x, y, 0);
            set_flag(x, y);
            break;

        case (CS_MINE | 0000000000):
        case (CS_MINE | CS_VISIBLE):
            win_num_print(0, 0, 2);
            set_mine(x, y);
            break;

        case (CS_VISIBLE):
            win_num_print(0, 0, 3);
            set_number(x, y, cell & 0x0f);
            break;

        default:
            win_num_print(0, 0, 255U);
            // draw_nothing(x, y);
            break;
    }
}

static void draw_plane(PlaneData_t *plane, u8 left, u8 top) {
    u8 w = PlaneData.get_width(plane);
    u8 h = PlaneData.get_height(plane);
    u8 cell = 0;
    for (u8 y = 0; y < h; y++) {
        for (u8 x = 0; x < w; x++) {
            cell = PlaneData.get_cell_state(plane, x, y);
            if (cell & CS_MINE) {
                set_mine(left + x, top + y);
            } else {
                set_number(left + x, top + y, cell & 0x0f);
            }
        }
    }
}

static void show_cursor(Cursor_t *cursor) {
    set_sprite_data(Cursor.get_nb(cursor), 1, Cursor.get_data(cursor));
    set_sprite_palette(Cursor.get_palette_nb(cursor), 1,
                       Cursor.get_palette(cursor));
    Cursor.move(cursor, 0, 0);
    move_sprite(Cursor.get_nb(cursor), 8 + Cursor.get_x(cursor) * 8,
                16 + Cursor.get_y(cursor) * 8);
}

static void scroll_cursor(Cursor_t *cursor, s8 dx, s8 dy, u8 w, u8 h) {
    u8 x = Cursor.get_x(cursor);
    u8 y = Cursor.get_y(cursor);
    x = (x + w + dx) % w;
    y = (y + h + dy) % h;
    Cursor.move(cursor, x, y);
    move_sprite(Cursor.get_nb(cursor), 8 + x * 8, 16 + y * 8);
}

static void draw_rect_of_blocks(u8 x, u8 y, u8 w, u8 h) {
    u8 *blocks = malloc(sizeof(u8) * w * h);

    VBK_REG = VBK_BANK_1;
    for (u8 i = 0; i < h; i++) {
        for (u8 j = 0; j < w; j++) {
            blocks[i * w + j] = 1;
        }
    }
    set_bkg_tiles(x, y, w, h, blocks);

    VBK_REG = VBK_BANK_0;
    for (u8 i = 0; i < h; i++) {
        for (u8 j = 0; j < w; j++) {
            blocks[i * w + j] = 0x26U;
        }
    }
    set_bkg_tiles(x, y, w, h, blocks);

    free(blocks);
}

// static void draw_gameover(void) {
//     u8 text[] = {40, 41, 42, 43, 44, 45, 43, 46};
//     set_win_tiles(6, 0, 8, 1, text);
// }

const struct GameVisualiserClass GameVisualiser = {

    .draw_plane = draw_plane,
    .draw_cell = draw_cell,
    .show_cursor = show_cursor,
    .scroll_cursor = scroll_cursor,
    .draw_rect_of_blocks = draw_rect_of_blocks,
    // .draw_nothing = draw_nothing,
    // .draw_gameover = draw_gameover,

};