#ifndef __GO_VISUALISER_H
#define __GO_VISUALISER_H

#include "../../include/short_types.h"

extern const struct GOVisualiserClass {
    void (*draw_gameover)(void);
} GOVisualiser;

#endif  //__GO_VISUALISER_H