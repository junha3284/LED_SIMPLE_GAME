#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

enum Joystick_input {
    None = -1,
    Up,
    Right,
    Down,
    Left,
};

typedef enum Joystick_input Joystick_input;

int Joystick_init();

void Joystick_finish();

// read user input from joystick
// -1: no input yet
// 0: up
// 1: right
// 2: down
// 3: left
Joystick_input Joystick_read();

#endif
