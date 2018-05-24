#ifndef _LED_H_
#define _LED_H_

// prepare all files and change all LEDs trigger to none
int LED_init();

// close all LED files
void LED_finish();

// turn on i_th LED on beaglebone (i starts from 0)
int LED_turn_on(int i);

// turn off i_th LED on beaglebone (i starts from 0)
int LED_turn_off(int i);

// blick LED
// @i ms on
// @j ms off
int LED_blink(int i, int j);

// blick LED
// @i: ms on
// @j: ms off
// @times: how many times blink
int LED_blink_times(int i, int j, int times);

#endif
