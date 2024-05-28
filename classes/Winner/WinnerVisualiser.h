#ifndef __WINNER_VISUALISER_H
#define __WINNER_VISUALISER_H

#include "../../include/short_types.h"

extern const struct WinnerVisualiserClass {
    void (*draw_winner)(void);
} WinnerVisualiser;

#endif  // __WINNER_VISUALISER_H