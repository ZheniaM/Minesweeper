#include "GameVisualiser.h"

#include "../include/BKG.h"

static void draw_plane(DataPlane_t *plane) {
    u8 w = DataPlane.get_width(plane);
    u8 h = DataPlane.get_height(plane);
    u8 *data = DataPlane.get_data(plane);
    BKG.set_tiles(0, 0, w, h, data);
}

const struct GameVisualiserClass GameVisualiser = {

    .draw_plane = draw_plane,

};