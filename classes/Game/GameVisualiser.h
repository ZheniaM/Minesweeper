#ifndef __GAME_VISUALISER_H
#define __GAME_VISUALISER_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "../../include/short_types.h"
#include "DataPlane.h"

typedef struct GameVisualiser_t GameVisualiser_t;
typedef GameVisualiser_t* pGameVisualiser_t;

extern const struct GameVisualiserClass {
    void (*draw_plane)(DataPlane_t* plane);
} GameVisualiser;

#endif  // __GAME_VISUALISER_H