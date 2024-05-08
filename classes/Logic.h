#ifndef __LOGIC_H
#define __LOGIC_H

typedef struct Logic {
    void (*process_joypad)(u8 joy);
} Logic;

#endif  // __LOGIC_H