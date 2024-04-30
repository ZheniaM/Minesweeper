#ifndef __BKG_H
#define __BKG_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "short_types.h"

extern const struct BKGClass {
    void (*get_data)(u8 firstTile, u8 nbTiles, pu8 data);
    u8 (*get_tile_xy)(u8 x, u8 y);
    void (*get_tiles)(u8 x, u8 y, u8 w, u8 h, pu8 tiles);
    pu8 (*get_xy_addr)(u8 x, u8 y);

    pu8 (*set_attribute_xy)(u8 x, u8 y, u8 attr);
    void (*set_attributes)(u8 x, u8 y, u8 w, u8 h, const pu8 tiles);
    void (*set_based_submap)(u8 x, u8 y, u8 w, u8 h, const pu8 map, u8 mapW,
                             u8 baseTile);
    void (*set_data)(u16 start, u16 nbTiles, const void *src);

    void (*set_palette)(u8 firstPalette, u8 nbPalettes,
                        const palette_color_t *rgbData);
    void (*set_palette_entry)(u8 palette, u8 entry, u16 rgbData);
    void (*set_submap)(u8 x, u8 y, u8 w, u8 h, const pu8 map, u8 mapW);

    void (*set_submap_attributes)(u8 x, u8 y, u8 w, u8 h, const pu8 map,
                                  u8 mapW);
    pu8 (*set_tile_xy)(u8 x, u8 y, u8 t);
    void (*set_tiles)(u8 x, u8 y, u8 w, u8 h, const pu8 tiles);

    void (*fill_rect)(u8 x, u8 y, u8 w, u8 h, u8 tile);
    void (*move)(u8 x, u8 y);
    void (*scroll)(s8 x, s8 y);
} BKG;

#endif  // __BKG_H