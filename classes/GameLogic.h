#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "GameEnums.h"
#include "Plane.h"

typedef struct GameState_t GameState_t;

extern const struct GameStateClass {
    void (*init)(GameState_t *self, GameStateSizes size);
    void (*set_flag)(GameState_t *self, u8 x, u8 y);
    BOOLEAN (*clean_cell)(GameState *self, u8 x, u8 y);
} GameState;

#endif  // __GAME_LOGIC_H