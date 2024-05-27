#ifndef __TITLE_VISUALISER_H
#define __TITLE_VISUALISER_H

#include "../../include/short_types.h"

extern const struct TitleVisualiserClass {
    void (*init)(void);
    void (*move_win)(u8 y);
    // prints h, w, mines numbers on win screen
    void (*print_nums)(u8 h, u8 w, u8 mines);
    void (*draw_active_h)(void);
    void (*draw_active_w)(void);
    void (*draw_active_mines)(void);
    void (*draw_active_start)(void);
    void (*draw_no_active)(void);
} TitleVisualiser;

#endif  //  __TITLE_VISUALISER_H