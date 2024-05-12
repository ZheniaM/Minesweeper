#ifndef __CURSOR_H
#define __CURSOR_H

#include <gb/cgb.h>
#include <gb/gb.h>
#include <stdlib.h>

#include "../../include/short_types.h"

typedef struct Cursor_t Cursor_t;

extern const struct CursorClass {
    Cursor_t *(*new)(u8 nb, u8 tile);
    void (*delete)(Cursor_t *self);
    void (*move)(Cursor_t *self, u8 x, u8 y);
    void (*scroll)(Cursor_t *self, s8 dx, s8 dy);
    u8 (*get_nb)(Cursor_t *self);
    u8 (*get_palette_nb)(Cursor_t *self);
    u8 *(*get_data)(Cursor_t *self);
    palette_color_t *(*get_palette)(Cursor_t *self);
    u8 (*get_x)(Cursor_t *self);
    u8 (*get_y)(Cursor_t *self);
} Cursor;

#endif  // __CURSOR_H