#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "LED.h"
#include "joystick.h"

int main()
{
    printf("Hello embedded world, from Junha Choi!\n");
    
    LED_init();
    joystick_init();
    
    printf("Press the Zen cape's Joystick in the direction of the LED.\n");
    printf("\t UP for LED 0 (top)\n");
    printf("\t Down for LED 3 (bottom)\n");
    printf("\t LEFT/RIGHT for exit app.\n");

    int i = -1;
    int answer;
    int trial = 0;
    int score = 0;

    while (1){        
        printf("Press joystick; current score (%d / %d)\n", score, trial);
        
        answer = rand()%2;
        printf("turn_on:%d\n", answer*3);
        LED_turn_on(answer*3);
        
        while( i == -1){
            i = joystick_read();
            sleep(1);
        }
        
        printf("turn_off:%d\n", answer*3);
        LED_turn_off(answer*3);

        if (i == answer*2){
            printf("Corect!\n");
            score++;
        }
        else if (i == 1 || i == 3){
            break;
        }
        else {
            printf("Incorrect! :(\n");
        }
        trial++;
        i = -1;
    }


    printf("Your final score was (%d / %d)\n", score, trial);
    printf("Thank you for playing!\n");
    
    
    LED_finish();
    joystick_finish();
    return 0;
}
