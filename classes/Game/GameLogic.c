#include "GameLogic.h"

typedef struct GameState_t {
    u16 score;
    DataPlane_t *plane;
    Cursor_t *cursor;

} GameState_t;

GameLogic_t new(DataPlane_t plane, Cursor_t cursore) {
    GameLogic_t *self = malloc(sizeof(GameState_t))
}