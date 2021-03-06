#include <stdio.h>
#include <time.h>
#include "LED.h"

#define LED_FILE_PRE "/sys/class/leds/beaglebone:green:usr"
#define LED_TRIGGER_SUF "/trigger"
#define LED_BRIGHTNESS_SUF "/brightness"
#define LED_DELAY_ON_SUF "/delay_on"
#define LED_DELAY_OFF_SUF "/delay_off"

#define LED_SIZE 4

#define PATH_MAX_LENGTH 64 

static FILE *pLEDTris[LED_SIZE];
static FILE *pLEDBri[LED_SIZE];

int LED_init()
{
    char buf[PATH_MAX_LENGTH];
    for (int i=0; i < LED_SIZE; i++){
        snprintf(buf, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_TRIGGER_SUF);
        pLEDTris[i] = fopen(buf, "w");
        int charWritten = fprintf(pLEDTris[i], "none");
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE INITIATING");
            return 1;
        }
        rewind(pLEDTris[i]);

        snprintf(buf, PATH_MAX_LENGTH, "%s%d%s", LED_FILE_PRE, i, LED_BRIGHTNESS_SUF);
        pLEDBri[i] = fopen(buf, "w");
        charWritten = fprintf(pLEDBri[i], "%d", 0);
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE TURNING OFF");
            return 1;
        }
        rewind(pLEDBri[i]);
    }
    return 0;
}

void LED_finish()
{
    for (int i=0; i< LED_SIZE; i++){
        fclose(pLEDTris[i]);
        fclose(pLEDBri[i]);
    }
}


// i: i_th LED (i starts from 0)
// j: 0 => turn off
//    1 => turn on 
static int LED_turn(int i, int j)
{
    if ( i < 0 || i >= LED_SIZE){
        printf("ERROR: THERE IS NO %d_th LED\n", i);
        return 1;
    }

    int charWritten = fprintf(pLEDBri[i], "%d", j);
    if (charWritten <= 0){
        printf("ERROR WRITING DATA WHILE TURNING ON LED");
    }
    rewind(pLEDBri[i]);
    return 0;
}

int LED_turn_on(int i)
{
   return LED_turn(i,1); 
}

int LED_turn_off(int i)
{
   return LED_turn(i,0); 
}

// blick LED with on_time (ms) and off_time (ms)
int LED_blink(int on_time, int off_time)
{
    for (int i=0; i < LED_SIZE; i++){
        int charWritten = fprintf(pLEDTris[i], "timer");  
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE BLICKING LED");
            return 0;
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
            return 1;
        }
    }

    for (int i=0; i < LED_SIZE; i++){
        fclose(pLEDDelayOn[i]);
        fclose(pLEDDelayOff[i]);
    }
    return 0;
}

// blick LED
// @times: how many times blink
int LED_blink_times(int on_time, int off_time, int times)
{
    for (int i=0; i < LED_SIZE; i++){
        int charWritten = fprintf(pLEDTris[i], "timer");  
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE BLICKING LED");
            return 1;
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
            return 1;
        }
    }

    int total_miliseconds = (on_time + off_time)*times;
    long seconds = (long) (total_miliseconds / 1000);
    long nanoseconds = (long) (total_miliseconds % 1000);
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
    
    for (int i=0; i < LED_SIZE; i++){
        fclose(pLEDDelayOn[i]);
        fclose(pLEDDelayOff[i]);
    }

    for (int i=0; i < LED_SIZE; i++){
        int charWritten = fprintf(pLEDTris[i], "none");  
        if (charWritten <= 0){
            printf("ERROR WRITING DATA WHILE BLICKING LED");
            return 1;
        }
        rewind(pLEDTris[i]);
    }
    return 0;
}
