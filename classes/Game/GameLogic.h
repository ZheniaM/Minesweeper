#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include "../../include/short_types.h"
#include "../Logic.h"

extern const struct GameLogicClass {
    void (*make)(u8 w, u8 h, u8 numOfMines);
    Logic logic;
    void (*delete)(void);
} GameLogic;

#endif  // __GAME_LOGIC_H