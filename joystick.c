#include <stdio.h>
#include <string.h>
#include "joystick.h"

#define GPIO_PRE "/sys/class/gpio/gpio"
#define GPIO_VALUE_SUF "/value"

// Joystick Up, Right, Down, Left GPIO numbers
#define GPIO_UP 26
#define GPIO_RT 47
#define GPIO_DN 46
#define GPIO_JSLFT 65

#define JOYSTICK_SIZE 4
#define PATH_MAX_LENGTH 32 

static FILE *pJoystickVal[JOYSTICK_SIZE];
static int gpio_nums[JOYSTICK_SIZE] = {GPIO_UP, GPIO_RT, GPIO_DN, GPIO_JSLFT};

int Joystick_init()
{
    char buf[32];
    for (int i=0; i < JOYSTICK_SIZE; i++){
        snprintf(buf, 32, "%s%d%s", GPIO_PRE, gpio_nums[i], GPIO_VALUE_SUF);
        pJoystickVal[i] = fopen(buf, "r");
        if (pJoystickVal[i] == NULL){
            printf("ERROR: Unable to open file (%s) for read\n", buf);
            return 1; 
        }
    }
    return 0;
}

void Joystick_finish()
{
    for (int i=0; i < JOYSTICK_SIZE; i++){
        fclose(pJoystickVal[i]);
    }
}

// -1: None 
// 0: Up
// 1: Right
// 2: Down 
// 3: Left
Joystick_input Joystick_read()
{
    char c;
    Joystick_init();
    for (int i=0; i < JOYSTICK_SIZE; i++){
        c = fgetc(pJoystickVal[i]);
        rewind(pJoystickVal[i]);
        if (c == '0')
           return i;
    }
    return -1;
}
