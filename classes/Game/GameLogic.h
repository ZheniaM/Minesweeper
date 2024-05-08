#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "../Logic.h"
#include "Cursor.h"
#include "DataPlane.h"
#include "GameEnums.h"

typedef struct GameLogic_t GameLogic_t;

extern const struct GameLogicClass {
    GameLogic_t *(*new)(DataPlane_t plane, Cursor_t cursor);
    // void (*)

} GameLogic;

#endif  // __GAME_LOGIC_H