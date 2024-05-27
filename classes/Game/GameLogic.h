#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include "../../include/short_types.h"
#include "../Logic.h"

extern struct GameLogicClass {
    Logic *logic;
    void (*start)(void);  //(u8 w, u8 h, u8 numOfMines);
} GameLogic;

#endif  // __GAME_LOGIC_H