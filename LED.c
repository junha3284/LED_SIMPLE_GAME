#include <stdio.h>
#include "LED.h"

#define LED_FILE_PRE "/sys/class/leds/beaglebone:green:usr"
#define LED_TRIGGER_SUF "/trigger"
#define LED_BRIGHTNESS_SUF "/brightness"
#define LED_SIZE 4

static FILE *pLEDTris[LED_SIZE];

void LED_init()
{
    char buf[50];
    for(int i=0; i < LED_SIZE; i++){
        snprintf(buf, 50, "%s%d%s", LED_FILE_PRE, i, LED_TRIGGER_SUF);
        pLEDTris[i] = fopen(buf, "w");
        int charWritten = fprintf(pLEDTris[i], "none");
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE INITIATING");
        }
    }
    for (int i=0; i < LED_SIZE; i++){
        fclose(pLEDTris[i]);
    }
}

// j: 0 => turn off
// j: 1 => turn on
// i: i_th LED
static void LED_turn(int i, int j)
{
    if ( i < 0 || i >= LED_SIZE){
        printf("ERROR: THERE IS NO %d_th LED\n", i);
        return;
    }
    
    char buf[50];
    snprintf(buf, 50, "%s%d%s", LED_FILE_PRE, i, LED_BRIGHTNESS_SUF);
    
    FILE *pLEDBri = fopen(buf, "w");

    int charWritten = fprintf(pLEDBri, "%d", j);
    if (charWritten <= 0){
        printf("ERROR WRITING DATA WHILE TURNING ON");
    }
    fclose(pLEDBri);
}

void LED_turn_on(int i)
{
   LED_turn(i,1); 
}

void LED_turn_off(int i)
{
   LED_turn(i,0); 
}

