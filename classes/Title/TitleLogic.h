#ifndef __TITLE_LOGIC_H
#define __TITLE_LOGIC_H

#include "../../include/short_types.h"
#include "../Logic.h"

extern struct TitleLogicClass {
    Logic *logic;
    void (*start)(void);
} TitleLogic;

#endif  //  __TITLE_LOGIC_H