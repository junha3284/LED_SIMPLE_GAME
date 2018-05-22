#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "LED.h"
#include "joystick.h"

#define LED_RIGHT_BLINK_DURATION 500
#define LED_WRONG_BLINK_DURATION 200

#define LED_RIGHT_BLINK_NUM 1
#define LED_WRONG_BLINK_NUM 5

int main()
{
    printf("Hello embedded world, from Junha Choi!\n\n");
    
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
       
        // answer is 0 or 1 
        answer = rand()%2;
        
        // Turn on top LED if answer is 0
        // otherwise, turn on bottom LED
        LED_turn_on(answer*3);
        
        // Get User input from joystick
        while( i == -1){
            i = joystick_read();
            sleep(1);
        }
        
        // Turn off the turned on LED
        LED_turn_off(answer*3);

        // If user got the correct answer, blink LED 1 times and give one score
        // If user got the wrong answer, blink LED 5 times 
        // If user put Joystick left or right, finish the loop
        if (i == answer*2){
            printf("Corect!\n");
            LED_blink_times(LED_RIGHT_BLINK_DURATION, LED_RIGHT_BLINK_DURATION, LED_RIGHT_BLINK_NUM);
            score++;
        }
        else if (i == 1 || i == 3){
            break;
        }
        else {
            printf("Incorrect! :(\n");
            LED_blink_times(LED_WRONG_BLINK_DURATION, LED_WRONG_BLINK_DURATION, LED_WRONG_BLINK_NUM);
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
