#include "Sprite.h"

// typedef struct Sprite_t {
//     u8 nb;
// } Sprite_t;

static u8 _get_prop(Sprite_nb_t self) {  //
    return get_sprite_prop(self);
}

static u8 _get_tile(Sprite_nb_t self) {  //
    return get_sprite_tile(self);
}

static void _set_prop(Sprite_nb_t self, u8 prop) {  //
    set_sprite_prop(self, prop);
}

static void _set_tile(Sprite_nb_t self, u8 tile) {  //
    set_sprite_tile(self, tile);
}

static void _hide(Sprite_nb_t self) {  //
    hide_sprite(self);
}

static void _move(Sprite_nb_t self, u8 x, u8 y) {  //
    move_sprite(self, x, y);
}

static void _scroll(Sprite_nb_t self, s8 x, s8 y) {  //
    scroll_sprite(self, x, y);
}

const struct SpriteClass Sprite = {

    .get_prop = _get_prop,
    .get_tile = _get_tile,
    .set_prop = _set_prop,
    .set_tile = _set_tile,
    .hide = _hide,
    .move = _move,
    .scroll = _scroll

};