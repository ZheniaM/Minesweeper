#ifndef __PLANE_H
#define __PLANE_H

#include <gb/gb.h>
#include <rand.h>
#include <stdlib.h>

#include "../../include/short_types.h"
#include "GameEnums.h"

typedef struct DataPlane_t DataPlane_t;

extern const struct DataPlaneClass {
    DataPlane_t *(*new)(PlaneSize size);
    void (*delete)(DataPlane_t *self);
    pu8 (*get_data)(DataPlane_t *self);
    u8 (*get_width)(DataPlane_t *self);
    u8 (*get_height)(DataPlane_t *self);
    CellState (*get_cell_state)(DataPlane_t *self, u8 x, u8 y);
    void (*set_flag)(DataPlane_t *self, u8 x, u8 y);
    CleanResult (*clean_from_mine)(DataPlane_t *self, u8 x, u8 y);
} DataPlane;

#endif  // __PLANE_H