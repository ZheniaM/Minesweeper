#include "DataPlane.h"

typedef struct DataPlane_t {
    u8 w;
    u8 h;
    u8 *data;
} DataPlane_t;

static const CellState const FRIEND_CONVERTER[] = {
    C_EMPTY, C_V1, C_V2, C_V3, C_V4, C_V5, C_V6, C_V7, C_V8,
};

static void add_number(DataPlane_t *self, u8 x, u8 y, u8 h, u8 w) {
    u8 state = self->data[y * h + x];
    u8 frieds = 0;
    if (C_EMPTY == state) {
        for (s8 i = -1; i <= 1; i++) {
            for (s8 j = -1; j <= 1; j++) {
                u8 ii = (h + y + i) % h;
                u8 jj = (w + x + j) % h;
                frieds += self->data[ii * h + jj] == C_MINE ? 1 : 0;
            }
        }
        if (0 == frieds) {
            self->data[y * h + x] = C_EMPTY;
        } else if (1 == frieds) {
            self->data[y * h + x] = C_V1;
        } else if (2 == frieds) {
            self->data[y * h + x] = C_V2;
        } else if (3 == frieds) {
            self->data[y * h + x] = C_V3;
        } else if (4 == frieds) {
            self->data[y * h + x] = C_V4;
        } else if (5 == frieds) {
            self->data[y * h + x] = C_V5;
        } else if (6 == frieds) {
            self->data[y * h + x] = C_V6;
        } else if (7 == frieds) {
            self->data[y * h + x] = C_V7;
        } else if (8 == frieds) {
            self->data[y * h + x] = C_V8;
        }
    }
}

static void fill_plane(DataPlane_t *self) {
    initrand((u16)DIV_REG);
    u8 h = self->h;
    u8 w = self->w;
    for (u8 y = 0; y < h; y++) {
        for (u8 x = 0; x < w; x++) {
            u8 r = rand();
            u8 putMine = r & 0b01 && r & 0b10;
            self->data[y * h + x] = (putMine ? C_MINE : C_EMPTY);
        }
    }
    // for (u8 y = 0; y < h; y++) {
    //     for (u8 x = 0; x < w; x++) {
    //         add_number(self, x, y, h, w);
    //     }
    // }
}

static DataPlane_t *new(PlaneSize size) {
    DataPlane_t *plane = malloc(sizeof(DataPlane_t));
    u16 s = 0;
    switch (size) {
        case PS_10x10:
            plane->h = 10;
            plane->w = 10;
            s = 10 * 10;
            break;
        case PS_16x16:
            plane->h = 16;
            plane->w = 16;
            s = 16 * 16;
            break;
        case PS_32x32:
            plane->h = 32;
            plane->w = 32;
            s = 32 * 32;
            break;
        default:
            plane->h = 4;
            plane->w = 4;
            s = 4 * 4;
            break;
    }
    plane->data = malloc(s * sizeof(u8));
    fill_plane(plane);
    return plane;
}

static CellState get_cell_state(DataPlane_t *self, u8 x, u8 y) {
    u8 h = self->h;
    u8 w = self->w;
    u8 cell = self->data[y * h + x];
    if (C_MINE == cell) {
        return C_MINE;
    }
    u8 friends = 0;
    u8 yy = 0;
    u8 xx = 0;
    for (s8 dy = -1; dy <= 1; dy++) {
        for (s8 dx = -1; dx <= 1; dx++) {
            yy = (h + y + dy) % h;
            xx = (w + x + dx) % w;
            friends += (self->data[yy * h + xx] == C_MINE);
        }
    }
    return FRIEND_CONVERTER[friends];
}

static void set_flag(DataPlane_t *self, u8 x, u8 y) {
    u8 h = self->h;
    self->data[y * h + x] = C_FLAG;
}

static CleanResult clean_from_mine(DataPlane_t *self, u8 x, u8 y) {
    u8 path = y * self->h + x;
    return C_MINE == self->data[path] ? CR_MINEHERE : CR_SUCCESS;
}

static u8 *get_plane_data(DataPlane_t *self) { return self->data; }
static u8 get_width(DataPlane_t *self) { return self->w; }
static u8 get_height(DataPlane_t *self) { return self->h; }

static void delete(DataPlane_t *self) {
    free(self->data);
    free(self);
}

const struct DataPlaneClass DataPlane = {

    .new = new,
    .delete = delete,
    .get_data = get_plane_data,
    .get_width = get_width,
    .get_height = get_height,
    .get_cell_state = get_cell_state,
    .set_flag = set_flag,
    .clean_from_mine = clean_from_mine,

};