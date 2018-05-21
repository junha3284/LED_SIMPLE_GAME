#include <stdio.h>
#include <unistd.h>
#include "LED.h"
#include "joystick.h"

int main()
{
    printf("Hello embedded world, from Junha Choi!\n");
    LED_init();
    joystick_init();
    LED_turn_on(0);
    LED_finish();
    int i = -1;
    while (i == -1){
        printf("sleeping\n");
        sleep(1);
        i = joystick_read();
    }
    printf("%d\n", joystick_read());
    joystick_finish();
    return 0;
}
