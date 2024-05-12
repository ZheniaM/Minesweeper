#ifndef __PLANE_FABRIC_H
#define __PLANE_FABRIC_H

#include "PlaneData.h"

extern const struct PlaneFabricClass {
    // max width and height can be 32, otherwise they will be 32
    PlaneData_t *(*generate)(u8 w, u8 h, u8 numMines);
} PlaneFabric;

#endif  // __PLANE_FABRIC_H
