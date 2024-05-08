#ifndef __OAM_H
#define __OAM_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "short_types.h"

extern const struct OAMClass {
    void (*get_data)(u8 firstTile, u8 nbTiles, pu8 data);
    void (*set_data)(u8 firstTile, u8 nbTiles, const pu8 data);
    void (*set_native_data)(u8 firstTile, u8 nbTiles, const pu8 data);
    void (*set_palette)(u8 firstPalette, u8 nbPalettes,
                        const palette_color_t *rgbData);
    void (*set_palette_entry)(u8 palette, u8 entry, u16 rgb_data);
} OAM;

#endif  // __OAM_H