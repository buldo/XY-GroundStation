#ifndef KEYPAD_KEY_H
#define KEYPAD_KEY_H
#include "pico/stdlib.h"

struct KeypadKey
{
    uint pin;
    uint32_t lvglKey;
};
#endif // DOG_H