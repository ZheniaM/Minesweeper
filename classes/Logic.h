#ifndef __LOGIC_H
#define __LOGIC_H

#include <gb/gb.h>

#include "../include/short_types.h"

#define IDLE_SCENE 0U
#define TITLE_SCENE 1U
#define GAME_SCENE 2U
#define END_SCENE 4U
#define GAMEOVER_SCENE 8U

typedef struct LogicClass {
    /*
        returns:
        IDLE_SCENE if scene doesn't change
        TITLE_SCENE
        GAME_SCENE
        END_SCENE
    */
    u8 (*make_cycle)(void);
    void (*delete)(void);
} Logic;

#endif  // __LOGIC_H