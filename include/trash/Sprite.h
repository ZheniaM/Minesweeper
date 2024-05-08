#ifndef __SPRITE_H
#define __SPRITE_H

#include <gb/cgb.h>
#include <gb/gb.h>

#include "short_types.h"

typedef u8 Sprite_nb_t;

extern const struct SpriteClass {
    // void (*new)(Sprite_nb_t empty, u8 nb);

    u8 (*get_prop)(Sprite_nb_t self);
    u8 (*get_tile)(Sprite_nb_t self);

    void (*set_prop)(Sprite_nb_t self, u8 prop);
    void (*set_tile)(Sprite_nb_t self, u8 tile);

    void (*hide)(Sprite_nb_t self);
    void (*move)(Sprite_nb_t self, u8 x, u8 y);
    void (*scroll)(Sprite_nb_t self, s8 x, s8 y);
} Sprite;

#endif  // __SPRITE_H