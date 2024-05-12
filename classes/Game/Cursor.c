#include "Cursor.h"

#include "../../data/cursores.h"

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

static Cursor_t *new(u8 nb, u8 tile) {
    Cursor_t *self = malloc(sizeof(Cursor_t));
    self->nb = nb;
    self->data = cursoreData;
    self->nbPalette = cursoreDataCGB[0];
    self->palette = cPalette;
    self->x = 0;
    self->y = 0;
    set_sprite_tile(nb, tile);
    return self;
}

static void move(Cursor_t *self, u8 x, u8 y) {
    self->x = x;
    self->y = y;
}

static void scroll(Cursor_t *self, s8 dx, s8 dy) {
    self->x += dx;
    self->y += dy;
}

static palette_color_t *_get_palette(Cursor_t *self) { return self->palette; }
static u8 get_nb_palette(Cursor_t *self) { return self->nbPalette; }
static u8 *_get_data(Cursor_t *self) { return self->data; }
static u8 get_nb(Cursor_t *self) { return self->nb; }
static u8 get_x(Cursor_t *self) { return self->x; }
static u8 get_y(Cursor_t *self) { return self->y; }
static void delete(Cursor_t *self) { free(self); }

const struct CursorClass Cursor = {

    .new = new,
    .delete = delete,
    .move = move,
    .scroll = scroll,
    .get_nb = get_nb,
    .get_data = _get_data,
    .get_palette = _get_palette,
    .get_palette_nb = get_nb_palette,
    .get_x = get_x,
    .get_y = get_y,

};