#include "BKG.h"

static void _get_data(u8 firstTile, u8 nbTiles, pu8 data) {
    get_bkg_data(firstTile, nbTiles, data);
}

static u8 _get_tile_xy(u8 x, u8 y) { return get_bkg_tile_xy(x, y); }

static void _get_tiles(u8 x, u8 y, u8 w, u8 h, pu8 tiles) {
    get_bkg_tiles(x, y, w, h, tiles);
}

static pu8 _get_xy_addr(u8 x, u8 y) { return get_bkg_xy_addr(x, y); }

static pu8 _set_attr_xy(u8 x, u8 y, u8 attr) {
    return set_bkg_attribute_xy(x, y, attr);
}

static void _set_attributes(u8 x, u8 y, u8 w, u8 h, const pu8 tiles) {
    set_bkg_attributes(x, y, w, h, tiles);
}

static void _set_based_submap(u8 x, u8 y, u8 w, u8 h, const pu8 map, u8 mapW,
                              u8 baseTile) {
    set_bkg_based_submap(x, y, w, h, map, mapW, baseTile);
}

static void _set_data(u16 start, u16 nbTiles, const void *src) {
    set_bkg_data(start, nbTiles, src);
}

static void _set_palette(u8 firstPalette, u8 nbPalettes,
                         const palette_color_t *rgbData) {
    set_bkg_palette(firstPalette, nbPalettes, rgbData);
}

static void _set_palette_entry(u8 palette, u8 entry, u16 rgbData) {
    set_bkg_palette_entry(palette, entry, rgbData);
}

static void _set_submap(u8 x, u8 y, u8 w, u8 h, const pu8 map, u8 mapW) {
    set_bkg_submap(x, y, w, h, map, mapW);
}

static void _set_submap_attributes(u8 x, u8 y, u8 w, u8 h, const pu8 map,
                                   u8 mapW) {
    set_bkg_submap_attributes(x, y, w, h, map, mapW);
}

static pu8 _set_tile_xy(u8 x, u8 y, u8 t) { return set_bkg_tile_xy(x, y, t); }

static void _set_tiles(u8 x, u8 y, u8 w, u8 h, const pu8 tiles) {
    set_bkg_tiles(x, y, w, h, tiles);
}

static void _fill_rect(u8 x, u8 y, u8 w, u8 h, u8 tile) {
    fill_bkg_rect(x, y, w, h, tile);
}

static void _move(u8 x, u8 y) { move_bkg(x, y); }

static void _scroll(s8 x, s8 y) { scroll_bkg(x, y); }

const struct BKGClass BKG = {.get_data = _get_data,
                             .get_tile_xy = _get_tile_xy,
                             .get_tiles = _get_tiles,
                             .get_xy_addr = _get_xy_addr,
                             .set_based_submap = _set_based_submap,
                             .set_data = _set_data,
                             .set_palette = _set_palette,
                             .set_palette_entry = _set_palette_entry,
                             .set_submap = _set_submap,
                             .set_submap_attributes = _set_submap_attributes,
                             .set_tile_xy = _set_tile_xy,
                             .set_tiles = _set_tiles,
                             .fill_rect = _fill_rect,
                             .move = _move,
                             .scroll = _scroll};