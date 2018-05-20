#include <stdio.h>
#include <LED.h>

// Joystick value files
#define JSUP_VALUE "/sys/class/gpio/gpio26/value"
#define JSDOWN_VALUE "/sys/class/gpio/gpio46/value"
#define JSLEFT_VALUE "/sys/class/gpio/gpio65/value"
#define JSRIGHT_VALUE "/sys/class/gpio/gpio47/value"

void openLEDFiles();
void writeNoneToFile(FILE*);

int main()
{
    printf("Hello embedded world, from Junha Choi!\n");
    
    // open LEDs' Trigger Files
    FILE *pLedTris[4];    
    openLEDFiles(pLedTris);

    for(int i=0; i < 4; i++){
        if (pLedTris[i] == NULL){
            printf("ERROR OPENDING LED%d_TRIGGER file.", i);
        }
    }

    writeNoneToFile(pLedTris[0]);

    // close all trigger files
    for(int i=0; i < 4; i++){
        fclose(pLedTris[i]);
    }
    return 0;
}

void openLEDFiles(FILE **FileArr)
{
    FileArr[0] = fopen(LED0_TRIGGER, "w");
    FileArr[1] = fopen(LED1_TRIGGER, "w");
    FileArr[2] = fopen(LED2_TRIGGER, "w");
    FileArr[3] = fopen(LED3_TRIGGER, "w");
}

void writeNoneToFile(FILE* file){
    int charWritten = fprintf(file, "none");
    if (charWritten <= 0){
        printf("ERROR WRITING DATA");
    }
}
