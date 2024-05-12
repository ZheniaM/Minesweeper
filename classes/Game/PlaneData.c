#include "PlaneData.h"

#include "../../include/printer.h"
#include "__PlaneData.h"

#define g(self, x, y) ((self)->data[(y) * (self)->w + (x)])

static u8 get_cell_state(PlaneData_t *self, u8 x, u8 y) {
    u8 h = self->h;
    u8 w = self->w;
    u8 cell = self->data[y * w + x];
    if (cell & CS_HAS_FRIENDS) {
        return cell & 0x0f;
    }
    if (cell & CS_FLAG) {
        return cell;
    }
    if (cell & CS_MINE) {
        return cell;
    }
    u8 friends = 0;
    u8 yy = 0;
    u8 xx = 0;
    for (s8 dy = -1; dy <= 1; dy++) {
        for (s8 dx = -1; dx <= 1; dx++) {
            yy = (h + y + dy) % h;
            xx = (w + x + dx) % w;
            if (self->data[yy * w + xx] & CS_MINE) {
                friends++;
            }
        }
    }
    self->data[y * self->w + x] |= friends | CS_HAS_FRIENDS;
    return friends;
}

static void set_flag(PlaneData_t *self, u8 x, u8 y) {
    if (self->data[y * self->w + x] & CS_FLAG) {
        self->data[y * self->w + x] &= ~CS_FLAG;
    } else {
        self->data[y * self->w + x] |= CS_FLAG;
    }
}

static CleanResult clean_from_mine(PlaneData_t *self, u8 x, u8 y) {
    return (self->data[y * self->w + x] & CS_MINE) ? CR_MINEHERE : CR_SUCCESS;
}

static u8 *get_plane_data(PlaneData_t *self) { return self->data; }
static u8 get_height(PlaneData_t *self) { return self->h; }
static u8 get_width(PlaneData_t *self) { return self->w; }
static u8 get_mines(PlaneData_t *self) { return self->mines; }

static void delete(PlaneData_t *self) {
    free(self->data);
    free(self);
}

const struct PlaneDataClass PlaneData = {

    .delete = delete,
    .get_data = get_plane_data,
    .get_width = get_width,
    .get_height = get_height,
    .get_mines = get_mines,
    .get_cell_state = get_cell_state,
    .set_flag = set_flag,
    .clean_from_mine = clean_from_mine,

};