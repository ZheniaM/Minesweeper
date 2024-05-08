#ifndef __GAME_ENUMS_H
#define __GAME_ENUMS_H

typedef enum PlaneSize {
    PS_10x10,
    PS_16x16,
    PS_32x32,
} PlaneSize;

typedef enum CellState {
    C_EMPTY,
    C_V1,
    C_V2,
    C_V3,
    C_V4,
    C_V5,
    C_V6,
    C_V7,
    C_V8,
    C_FLAG,
    C_MINE,
} CellState;

typedef enum CleanResult {
    CR_SUCCESS,
    CR_MINEHERE,
} CleanResult;

#endif  // __GAME_ENUMS_H
