#ifndef __GO_LOGIC_H
#define __GO_LOGIC_H

#include "../../include/short_types.h"
#include "../Logic.h"

extern struct GOLogicClass {
    Logic *logic;
    void (*start)(void);
} GOLogic;

#endif  // __GO_LOGIC_H