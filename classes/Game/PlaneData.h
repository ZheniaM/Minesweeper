#ifndef __PLANE_DATA_H
#define __PLANE_DATA_H

#include <gb/gb.h>
#include <rand.h>
#include <stdlib.h>

#include "../../include/short_types.h"
#include "GameEnums.h"

typedef struct PlaneData_t PlaneData_t;

extern const struct PlaneDataClass {
    void (*delete)(PlaneData_t *self);
    u8 *(*get_data)(PlaneData_t *self);
    u8 (*get_width)(PlaneData_t *self);
    u8 (*get_height)(PlaneData_t *self);
    u8 (*get_mines)(PlaneData_t *self);
    u8 (*get_cell_state)(PlaneData_t *self, u8 x, u8 y);
    // returns 1 if set and 0 if unset
    u8 (*set_flag)(PlaneData_t *self, u8 x, u8 y);
    // returns 1 if success and 0 if there was mine
    u8 (*clean_from_mine)(PlaneData_t *self, u8 x, u8 y);
} PlaneData;

#endif  // __PLANE_DATA_H