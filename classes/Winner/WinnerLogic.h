#ifndef __WINNER_LOGIC_H
#define __WINNER_LOGIC_H

#include "../../include/short_types.h"
#include "../Logic.h"

extern struct WinnerLogicClass {
    Logic *logic;
    void (*start)(void);
} WinnerLogic;

#endif  //  __WINNER_LOGIC_H