#ifndef __GAME_VISUALISER_H
#define __GAME_VISUALISER_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "../../include/short_types.h"
#include "Cursor.h"
#include "PlaneData.h"

typedef struct Inscription_t {
    const u8 size;
    const u8 x;
    const u8 y;
    const u8 *title;
} Inscription_t;

extern const struct GameVisualiserClass {
    void (*draw_plane)(PlaneData_t *plane, u8 x, u8 y);
    void (*draw_cell)(u8 cell, u8 x, u8 y);
    void (*draw_rect_of_blocks)(u8 x, u8 y, u8 w, u8 h);
    void (*draw_nothing)(u8 x, u8 y);
    // void (*draw_gameover)(void);
    void (*draw_inscriptions)(const u8 size, Inscription_t inscrs[size]);
    void (*show_cursor)(Cursor_t *cursor);
    void (*scroll_cursor)(Cursor_t *cursor, s8 dx, s8 dy, u8 w, u8 h);
    void (*centralize)(u8 h, u8 w);
} GameVisualiser;

#endif  // __GAME_VISUALISER_H