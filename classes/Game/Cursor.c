#include "Cursor.h"

typedef struct Cursor_t {
    u8 nb;
    u8 nbPalette;
    u8 x;
    u8 y;
    u8 *data;
    palette_color_t *palette;
} Cursor_t;

static palette_color_t cPalette[] = {
    cursoreDataCGBPal0c0,
    cursoreDataCGBPal0c1,
    cursoreDataCGBPal0c2,
    cursoreDataCGBPal0c3,
};

static Cursor_t cursor = {
    .nbPalette = 0,
    .palette = cPalette,
    .data = cursoreData,
};

static Cursor_t *make(u8 nb, u8 tile) {
    cursor.nb = nb;
    cursor.nbPalette = cursoreDataCGB[0];
    cursor.x = cursor.y = 0;
    set_sprite_tile(nb, tile);
    return &cursor;
}

static void move(u8 x, u8 y) {  //
    cursor.x = x;
    cursor.y = y;
}

static void scroll(s8 dx, s8 dy) {  //
    cursor.x += dx;
    cursor.y += dy;
}

static u8 get_nb(void) {  //
    return cursor.nb;
}

static u8 get_nb_palette(void) {  //
    return cursor.nbPalette;
}

static u8 *_get_data(void) {  //
    return cursor.data;
}

static palette_color_t *_get_palette(void) {  //
    return cursor.palette;
}

static u8 get_x(void) {  //
    return cursor.x;
}

static u8 get_y(void) {  //
    return cursor.y;
}

const struct CursorClass Cursor = {

    .make = make,
    .move = move,
    .scroll = scroll,
    .get_nb = get_nb,
    .get_data = _get_data,
    .get_palette = _get_palette,
    .get_palette_nb = get_nb_palette,
    .get_x = get_x,
    .get_y = get_y,

};