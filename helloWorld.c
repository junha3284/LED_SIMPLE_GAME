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
    
    int function_result = Joystick_init() || LED_init();
    if( function_result == 1){
        printf("ERROR: Joystick_init() failed\n");
        exit(1);
    }

    printf("Press the Zen cape's Joystick in the direction of the LED.\n");
    printf("\t UP for LED 0 (top)\n");
    printf("\t Down for LED 3 (bottom)\n");
    printf("\t LEFT/RIGHT for exit app.\n");

    Joystick_input user_input = None;
    int answer;
    int trial = 0;
    int score = 0;

    while (1){        
        printf("Press joystick; current score (%d / %d)\n", score, trial);
       
        // answer is 0 or 1 
        answer = rand()%2;
        
        // Turn on top LED if answer is 0
        // otherwise, turn on bottom LED
        function_result = LED_turn_on(answer*3);
        if( function_result == 1){
            printf("ERROR: LED_turn_on failed\n");
            exit(1);
        }
        
        // Get User input from joystick
        while( user_input == None){
            user_input = Joystick_read();
            sleep(1);
        }
        
        // Turn off the turned on LED
        function_result = LED_turn_off(answer*3);
        if( function_result == 1){
            printf("ERROR: LED_turn_off failed\n");
            exit(1);
        }

        // If user got the correct answer, blink LED 1 times and give one score
        // If user got the wrong answer, blink LED 5 times 
        // If user put Joystick left or right, finish the loop
        if (user_input == answer*2){
            printf("Corect!\n");
            function_result = LED_blink_times(LED_RIGHT_BLINK_DURATION, LED_RIGHT_BLINK_DURATION, LED_RIGHT_BLINK_NUM);
            if( function_result == 1){
                printf("ERROR: Joystick_init() failed\n");
                exit(1);
            }
            score++;
        }

        else if (user_input == Left || user_input == Right){
            break;
        }

        else {
            printf("Incorrect! :(\n");
            function_result = LED_blink_times(LED_WRONG_BLINK_DURATION, LED_WRONG_BLINK_DURATION, LED_WRONG_BLINK_NUM);
            if( function_result == 1){
                printf("ERROR: Joystick_init() failed\n");
                exit(1);
            }
        }
        trial++;
        user_input = None;
    }

    printf("Your final score was (%d / %d)\n", score, trial);
    printf("Thank you for playing!\n");
    
    LED_finish();
    Joystick_finish();
    return 0;
}
