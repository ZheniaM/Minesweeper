#ifndef __LOGIC_H
#define __LOGIC_H

#include <gb/gb.h>

#include "../include/short_types.h"

typedef struct LogicClass {
    // return 0 if scene don't change
    u8 (*make_cycle)(void);
} Logic;

#endif  // __LOGIC_H