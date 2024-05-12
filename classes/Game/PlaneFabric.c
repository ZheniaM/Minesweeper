#include "PlaneFabric.h"

#include <rand.h>
#include <stdlib.h>

#include "__PlaneData.h"

static void add_mines(PlaneData_t *self, u8 numMines) {
    initrand((u16)DIV_REG);

    u16 maxMines = self->h * self->w;
    maxMines = numMines > maxMines ? maxMines : numMines;
    self->mines = maxMines;
    for (u16 m = 0; m < maxMines;) {
        u16 r = randw();
        u8 y = r % self->h;
        u8 x = (r >> 8) % self->w;
        if (!self->data[y * self->w + x]) {
            self->data[y * self->w + x] |= CS_MINE;
            m++;
        }
    }
}

static PlaneData_t *generate(u8 w, u8 h, u8 numMines) {
    PlaneData_t *self = malloc(sizeof(PlaneData_t));
    self->h = (h > 32) ? 32 : h;
    self->w = (w > 32) ? 32 : w;
    self->data = malloc(sizeof(u8) * self->h * self->w);

    for (u8 i = 0; i < self->h; i++) {
        for (u8 j = 0; j < self->w; j++) {
            self->data[i * self->w + j] = CS_N0;
        }
    }
    add_mines(self, numMines);
    return self;
}

const struct PlaneFabricClass PlaneFabric = {

    .generate = generate,

};