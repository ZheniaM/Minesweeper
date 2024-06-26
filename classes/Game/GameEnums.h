#ifndef __GAME_ENUMS_H
#define __GAME_ENUMS_H

/* 0b<2nothing><1flag><1mine><4neighbours>

    exmaple:
    0b00000000 is 0 neighbours
    0b00001000 is 8 neighbours
    0b00010000 is mine
    0b00110000 is mine with flag
*/
enum CellState {
    CS_N0,
    CS_N1,
    CS_N2,
    CS_N3,
    CS_N4,
    CS_N5,
    CS_N6,
    CS_N7,
    CS_N8,
    CS_MINE = 0x10U,
    CS_FLAG = 0x20U,
    CS_VISIBLE = 0x40U,
};
#endif  // __GAME_ENUMS_H
