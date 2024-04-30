#include "OAM.h"

static void _get_data(u8 firstTile, u8 nbTiles, pu8 data) {
    get_sprite_data(firstTile, nbTiles, data);
}

static void _set_data(u8 firstTile, u8 nbTiles, const pu8 data) {
    set_sprite_data(firstTile, nbTiles, data);
}
static void _set_native_data(u8 firstTile, u8 nbTiles, const pu8 data) {
    set_sprite_native_data(firstTile, nbTiles, data);
}
static void _set_palette(u8 firstPalette, u8 nbPalettes,
                         const palette_color_t *rgbData) {
    set_sprite_palette(firstPalette, nbPalettes, rgbData);
}
static void _set_palette_entry(u8 palette, u8 entry, u16 rgbData) {
    set_sprite_palette_entry(palette, entry, rgbData);
}

const struct OAMClass OAM = {.get_data = _get_data,
                             .set_data = _set_data,
                             .set_native_data = _set_native_data,
                             .set_palette = _set_palette,
                             .set_palette_entry = _set_palette_entry};