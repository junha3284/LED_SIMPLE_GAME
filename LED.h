// prepare all files and change all LEDs trigger to none
void LED_init();

// close all LED files
void LED_finish();

// turn on i_th LED on beaglebone (i starts from 0)
void LED_turn_on(int i);

// turn off i_th LED on beaglebone (i starts from 0)
void LED_turn_off(int i);

// blick LED
// @i ms on
// @j ms off
void LED_blink(int i, int j);

// blick LED
// @i: ms on
// @j: ms off
// @times: how many times blink
void LED_blink_times(int i, int j, int times);
