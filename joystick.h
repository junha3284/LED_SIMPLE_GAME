void joystick_init();

void joystick_finish();

// read user input from joystick
// -1: no input yet
// 0: up
// 1: right
// 2: down
// 3: left
int joystick_read();
