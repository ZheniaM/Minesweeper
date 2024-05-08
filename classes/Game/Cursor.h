#ifndef __CURSOR_H
#define __CURSOR_H

#include <gb/cgb.h>
#include <gb/gb.h>
#include <stdlib.h>

#include "../../data/cursores.h"
#include "../../include/short_types.h"

typedef struct Cursor_t Cursor_t;

extern const struct CursorClass {
    Cursor_t *(*make)(u8 nb, u8 tile);
    void (*move)(u8 x, u8 y);
    void (*scroll)(s8 dx, s8 dy);
    u8 (*get_nb)(void);
    u8 (*get_palette_nb)(void);
    u8 *(*get_data)(void);
    palette_color_t *(*get_palette)(void);
    u8 (*get_x)(void);
    u8 (*get_y)(void);
} Cursor;

#endif  // __CURSOR_H