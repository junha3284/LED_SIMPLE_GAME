#include <stdio.h>
#include "LED.h"

// Joystick value files
#define JSUP_VALUE "/sys/class/gpio/gpio26/value"
#define JSDOWN_VALUE "/sys/class/gpio/gpio46/value"
#define JSLEFT_VALUE "/sys/class/gpio/gpio65/value"
#define JSRIGHT_VALUE "/sys/class/gpio/gpio47/value"

void writeNoneToFile(FILE*);

int main()
{
    printf("Hello embedded world, from Junha Choi!\n");
    LED_init();
    LED_turn_on(0);
    return 0;
}
