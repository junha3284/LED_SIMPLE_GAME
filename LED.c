#include <stdio.h>
#include <time.h>
#include "LED.h"

#define LED_FILE_PRE "/sys/class/leds/beaglebone:green:usr"
#define LED_TRIGGER_SUF "/trigger"
#define LED_BRIGHTNESS_SUF "/brightness"
#define LED_DELAY_ON_SUF "/delay_on"
#define LED_DELAY_OFF_SUF "/delay_off"

#define LED_SIZE 4

#define PATH_MAX_LENGTH 50

static FILE *pLEDTris[LED_SIZE];
static FILE *pLEDBri[LED_SIZE];

void LED_init()
{
    char buf[PATH_MAX_LENGTH];
    for (int i=0; i < LED_SIZE; i++){
        snprintf(buf, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_TRIGGER_SUF);
        pLEDTris[i] = fopen(buf, "w");
        int charWritten = fprintf(pLEDTris[i], "none");
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE INITIATING");
        }
        rewind(pLEDTris[i]);

        snprintf(buf, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_BRIGHTNESS_SUF);
        pLEDBri[i] = fopen(buf, "w");
        charWritten = fprintf(pLEDBri[i], "%d", 0);
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE TURNING OFF");
        }
        rewind(pLEDBri[i]);
    }
}

void LED_finish()
{
    for (int i=0; i< LED_SIZE; i++){
        fclose(pLEDTris[i]);
        fclose(pLEDBri[i]);
    }
}


// j: 0 => turn off
// j: 1 => turn on
// i: i_th LED (i starts from 0)
static void LED_turn(int i, int j)
{
    if ( i < 0 || i >= LED_SIZE){
        printf("ERROR: THERE IS NO %d_th LED\n", i);
        return;
    }

    int charWritten = fprintf(pLEDBri[i], "%d", j);
    if (charWritten <= 0){
        printf("ERROR WRITING DATA WHILE TURNING ON LED");
    }
    rewind(pLEDBri[i]);
}

void LED_turn_on(int i)
{
   LED_turn(i,1); 
}

void LED_turn_off(int i)
{
   LED_turn(i,0); 
}

// blick LED
// @i ms on
// @j ms off
void LED_blink(int on_time, int off_time)
{
    for (int i=0; i < LED_SIZE; i++){
        int charWritten = fprintf(pLEDTris[i], "timer");  
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE BLICKING LED");
        }
        rewind(pLEDTris[i]);
    }

    char buf1[PATH_MAX_LENGTH];
    char buf2[PATH_MAX_LENGTH];

    FILE *pLEDDelayOn[4];
    FILE *pLEDDelayOff[4];

    for (int i=0; i < LED_SIZE; i++){
        snprintf(buf1, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_DELAY_ON_SUF);
        snprintf(buf2, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_DELAY_OFF_SUF);

        pLEDDelayOn[i] = fopen(buf1, "w"); 
        pLEDDelayOff[i] = fopen(buf2, "w");
    }

    for (int i=0; i < LED_SIZE; i++){
        int charWritten1 = fprintf(pLEDDelayOn[i], "%d", on_time);
        int charWritten2 = fprintf(pLEDDelayOff[i], "%d", off_time);

        if (charWritten1 <= 0 || charWritten2 <= 0){
            printf("ERROR WRITING DATA WHILE WRITING DELAY DATA FOR LED");
        }
    }

    for (int i=0; i < LED_SIZE; i++){
        fclose(pLEDDelayOn[i]);
        fclose(pLEDDelayOff[i]);
    }
}

// blick LED
// @i ms on
// @j ms off
// @times: how many times blink
void LED_blink_times(int on_time, int off_time, int times)
{
    for (int i=0; i < LED_SIZE; i++){
        int charWritten = fprintf(pLEDTris[i], "timer");  
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE BLICKING LED");
        }
        rewind(pLEDTris[i]);
    }

    char buf1[PATH_MAX_LENGTH];
    char buf2[PATH_MAX_LENGTH];

    FILE *pLEDDelayOn[4];
    FILE *pLEDDelayOff[4];

    for (int i=0; i < LED_SIZE; i++){
        snprintf(buf1, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_DELAY_ON_SUF);
        snprintf(buf2, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_DELAY_OFF_SUF);

        pLEDDelayOn[i] = fopen(buf1, "w"); 
        pLEDDelayOff[i] = fopen(buf2, "w");
    }

    for (int i=0; i < LED_SIZE; i++){
        int charWritten1 = fprintf(pLEDDelayOn[i], "%d", on_time);
        int charWritten2 = fprintf(pLEDDelayOff[i], "%d", off_time);
        rewind(pLEDDelayOn[i]);
        rewind(pLEDDelayOff[i]);
        if (charWritten1 <= 0 || charWritten2 <= 0){
            printf("ERROR WRITING DATA WHILE WRITING DELAY DATA FOR LED");
        }
    }

    int total_miliseconds = (on_time + off_time)*times;
    long seconds = (long) (total_miliseconds / 1000);
    long nanoseconds = (long) (total_miliseconds % 1000);
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
    printf("%ld second, %ld nanoseconds\n", seconds, nanoseconds);
    
    for (int i=0; i < LED_SIZE; i++){
        fclose(pLEDDelayOn[i]);
        fclose(pLEDDelayOff[i]);
    }

    for (int i=0; i < LED_SIZE; i++){
        int charWritten = fprintf(pLEDTris[i], "none");  
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE BLICKING LED");
        }
        rewind(pLEDTris[i]);
    }
}
